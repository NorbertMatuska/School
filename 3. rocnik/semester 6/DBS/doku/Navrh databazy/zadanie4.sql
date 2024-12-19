CREATE TABLE Category (
    CategoryID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Description TEXT
);

CREATE TABLE Institution (
    InstitutionID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Type VARCHAR(100)
);

CREATE TABLE SpaceZone (
    SpaceID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Description TEXT
);

CREATE TABLE Exhibition (
    ExhibitionID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Description TEXT,
    StartDate DATE,
    EndDate DATE
);

CREATE TABLE ExhibitionSpaceZone (
    ExhibitionID INTEGER NOT NULL,
    SpaceID INTEGER NOT NULL,
    CONSTRAINT pk_ExhibitionSpace PRIMARY KEY(ExhibitionID, SpaceID),
    CONSTRAINT fk_exhibitionSpaceExhibition FOREIGN KEY(ExhibitionID) REFERENCES Exhibition(ExhibitionID),
    CONSTRAINT fk_exhibitionSpaceSpace FOREIGN KEY(SpaceID) REFERENCES SpaceZone(SpaceID)
);

CREATE TABLE Item (
    ItemID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Description TEXT,
    State VARCHAR(100),
    CategoryID INTEGER NOT NULL,
    CONSTRAINT fk_category FOREIGN KEY(CategoryID) REFERENCES Category(CategoryID)
);

CREATE TABLE ItemStateLog (
    LogID SERIAL PRIMARY KEY,
    ItemID INTEGER NOT NULL,
    State VARCHAR(100) NOT NULL,
    Date TIMESTAMP NOT NULL,
    Location VARCHAR(255),
    ExhibitionID INTEGER,
    CONSTRAINT fk_item FOREIGN KEY(ItemID) REFERENCES Item(ItemID),
    CONSTRAINT fk_exhibition FOREIGN KEY(ExhibitionID) REFERENCES Exhibition(ExhibitionID)
);

CREATE TABLE ItemInstitutionLoan (
    ItemID INTEGER NOT NULL,
    InstitutionID INTEGER NOT NULL,
    LoanStart DATE,
    LoanEnd DATE,
    CONSTRAINT pk_itemInstitution PRIMARY KEY(ItemID, InstitutionID),
    CONSTRAINT fk_itemLoan FOREIGN KEY(ItemID) REFERENCES Item(ItemID),
    CONSTRAINT fk_institution FOREIGN KEY(InstitutionID) REFERENCES Institution(InstitutionID)
);

CREATE TABLE ItemExhibition (
    ItemID INTEGER NOT NULL,
    ExhibitionID INTEGER NOT NULL,
    CONSTRAINT pk_itemExhibition PRIMARY KEY(ItemID, ExhibitionID),
    CONSTRAINT fk_itemExhibitionItem FOREIGN KEY(ItemID) REFERENCES Item(ItemID),
    CONSTRAINT fk_exhibitionItem FOREIGN KEY(ExhibitionID) REFERENCES Exhibition(ExhibitionID)
);

CREATE OR REPLACE FUNCTION check_item_exhibition_overlap()
RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (
        SELECT 1 FROM ItemExhibition ie
        INNER JOIN Exhibition e ON ie.ExhibitionID = e.ExhibitionID
        WHERE ie.ItemID = NEW.ItemID
        AND e.ExhibitionID <> NEW.ExhibitionID
        AND (
            (e.StartDate <= (SELECT EndDate FROM Exhibition WHERE ExhibitionID = NEW.ExhibitionID) 
            AND 
            e.EndDate >= (SELECT StartDate FROM Exhibition WHERE ExhibitionID = NEW.ExhibitionID))
        )
    ) THEN
        RAISE EXCEPTION 'Item is already part of an ongoing exhibition.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_check_exhibition_overlap
BEFORE INSERT ON ItemExhibition
FOR EACH ROW EXECUTE FUNCTION check_item_exhibition_overlap();

CREATE OR REPLACE FUNCTION check_item_available_before_exhibition()
RETURNS TRIGGER AS $$
DECLARE
    currentItemState VARCHAR(100);
BEGIN
    SELECT State INTO currentItemState
    FROM ItemStateLog
    WHERE ItemID = NEW.ItemID
    ORDER BY Date DESC, LogID DESC
    LIMIT 1;

    IF currentItemState IS DISTINCT FROM 'available' THEN
        RAISE EXCEPTION 'Only items in the state of ''available'' can be part of an exhibition, current state is: %', currentItemState;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_check_item_available
BEFORE INSERT ON ItemExhibition
FOR EACH ROW EXECUTE FUNCTION check_item_available_before_exhibition();


CREATE OR REPLACE FUNCTION check_spacezone_exhibition_overlap()
RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (
        SELECT 1 FROM ExhibitionSpaceZone esz
        INNER JOIN Exhibition e ON esz.ExhibitionID = e.ExhibitionID
        WHERE esz.SpaceID = NEW.SpaceID
        AND e.ExhibitionID != NEW.ExhibitionID
        AND NOT (
            NEW.StartDate > e.EndDate OR
            NEW.EndDate < e.StartDate
        )
    ) THEN
        RAISE EXCEPTION 'Another exhibition is already scheduled.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_check_spacezone_exhibition_overlap
BEFORE INSERT OR UPDATE ON ExhibitionSpaceZone
FOR EACH ROW EXECUTE FUNCTION check_spacezone_exhibition_overlap();

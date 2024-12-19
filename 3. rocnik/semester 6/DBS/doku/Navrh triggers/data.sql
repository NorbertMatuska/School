INSERT INTO Category (CategoryID, Name, Description) VALUES
(1, 'Painting', 'Artworks created using paints and brushes on a surface'),
(2, 'Sculpture', 'Three-dimensional artworks created by shaping materials'),
(3, 'Photography', 'Artworks created through the capture of light on a sensitive medium'),
(4, 'Textile', 'Artworks created using fibers and threads'),
(5, 'Digital', 'Artworks created or stored in digital formats'),
(6, 'Ceramics', 'Artworks made from clay and then hardened by heat'),
(7, 'Glass', 'Artworks created by molding or blowing glass'),
(8, 'Metalwork', 'Artworks crafted from various metals'),
(9, 'Woodwork', 'Artworks and objects crafted from wood'),
(10, 'Mixed Media', 'Artworks made from a combination of materials');

INSERT INTO Institution (InstitutionID, Name, Type) VALUES
(1, 'Museum of Modern Art', 'Museum'),
(2, 'National Gallery', 'Gallery'),
(3, 'City Library', 'Library'),
(4, 'Historical Museum', 'Museum'),
(5, 'Tech Hub Gallery', 'Gallery'),
(6, 'University Arts Center', 'Educational'),
(7, 'Private Collection', 'Private'),
(8, 'Cultural Heritage Institute', 'Research'),
(9, 'State Archive', 'Archive'),
(10, 'Art School Gallery', 'Educational');

INSERT INTO SpaceZone (SpaceID, Name, Description) VALUES
(1, 'Main Hall', 'The primary exhibition area of the institution'),
(2, 'Gallery One', 'A smaller, intimate gallery for special exhibits'),
(3, 'Sculpture Garden', 'Outdoor space for displaying large-scale sculptures'),
(4, 'Rooftop Terrace', 'Open air space suitable for events and installations'),
(5, 'Photography Wing', 'Dedicated area for photographic exhibitions'),
(6, 'Interactive Zone', 'Space for interactive and digital art installations'),
(7, 'Children’s Art Space', 'Area designed for children’s workshops and exhibitions'),
(8, 'Temporary Exhibit Room', 'Space for temporary or traveling exhibitions'),
(9, 'Video Art Corridor', 'Corridor lined with screens for video art'),
(10, 'Underground Vault', 'Secure area for high-value artworks');

INSERT INTO Exhibition (ExhibitionID, Name, Description, StartDate, EndDate) VALUES
(1, 'Impressions of Modernity', 'Exploring modern themes and expressions', '2024-05-01', '2024-08-31'),
(2, 'Sculptures of the Century', 'A collection of significant sculptures from the 20th century', '2024-09-16', '2024-12-15'),
(3, 'World in Frames', 'Photographic representations from around the globe', '2024-07-01', '2024-10-01'),
(4, 'Fabric of Society', 'Exhibition on the impact of textile in fashion and art', '2025-08-01', '2025-11-30'),
(5, 'Digital Dreams', 'Art in the age of technology', '2024-09-01', '2024-12-31'),
(6, 'Ceramic Forms', 'Evolution of ceramics from utility to art', '2024-10-02', '2025-01-31'),
(7, 'Glass Horizons', 'Exploring the artistic potential of glass', '2024-11-01', '2025-02-28'),
(8, 'Metal Mastery', 'Artworks showing the versatility of metal', '2026-01-01', '2026-04-30'),
(9, 'Wooden Wonders', 'Showcasing historical and contemporary woodcraft', '2026-02-01', '2026-05-31'),
(10, 'Media Mix', 'Exploration of mixed media in contemporary art', '2025-06-01', '2025-09-30');

INSERT INTO ExhibitionSpaceZone (ExhibitionID, SpaceID) VALUES
(1, 1), 
(2, 1),
(3, 5),
(4, 6), 
(5, 6), 
(6, 4),
(7, 2),
(8, 2), 
(9, 9),
(10, 9);

INSERT INTO Item (ItemID, Name, Description, State, CategoryID) VALUES
(1, 'Sunset Canvas', 'A beautiful painting of a sunset', 'available', 1),
(2, 'Bronze Horseman', 'Sculpture of a horseman made from bronze', 'loaned', 2),
(3, 'City Night Lights', 'Photograph of city lights at night', 'available', 3),
(4, 'Silk Embroidery', 'Traditional silk embroidery', 'restoration', 4),
(5, 'Virtual Reality Landscape', 'A digital creation of a fantasy landscape', 'available', 5),
(6, 'Porcelain Vase', 'Handcrafted porcelain vase from the 18th century', 'available', 6),
(7, 'Stained Glass Window', 'Colorful stained glass window design', 'available', 7),
(8, 'Iron Gate', 'Intricately designed iron gate', 'available', 8),
(9, 'Carved Wooden Box', 'Decoratively carved box made of oak', 'available', 9),
(10, 'Collage of Memories', 'Mixed media collage of vintage photographs', 'available', 10);

INSERT INTO ItemStateLog (ItemID, State, Date, SpaceID, ExhibitionID) VALUES
(1, 'available', NOW(), 1, 1),
(2, 'loaned', NOW(), NULL, NULL),
(3, 'available', NOW(), 5, 3),
(4, 'restoration', NOW(), NULL, NULL),
(5, 'available', NOW(), 6, 5),
(6, 'available', NOW(), 4, 6),
(7, 'available', NOW(), 2, 7),
(8, 'available', NOW(), 1, 8),
(9, 'available', NOW(), 9, 9),
(10, 'available', NOW(), 8, 10);

INSERT INTO ItemInstitutionLoan (ItemID, InstitutionID, LoanStart, LoanEnd) VALUES
(3, 3, '2024-01-01', '2024-12-31'),
(5, 2, '2024-01-01', '2024-03-31');

INSERT INTO ItemExhibition (ItemID, ExhibitionID) VALUES
(1, 1), (3, 3), (5, 5), (6, 6), (7, 7),
(8, 8), (9, 9), (10, 10), (1, 2), (3, 4);

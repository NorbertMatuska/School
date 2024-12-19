from fastapi import APIRouter, HTTPException, Query
from unidecode import unidecode
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v2/posts/")
def get_posts(query: str = Query(None, description="Query string"),
              duration: float = Query(None, description="Max duration"),
              limit: int = Query(None, description="Limit number of posts")):
    try:
        conn = psycopg2.connect(
            host=settings.DATABASE_HOST,
            database=settings.DATABASE_NAME,
            user=settings.DATABASE_USER,
            password=settings.DATABASE_PASSWORD,
            port=settings.DATABASE_PORT
        )
        cur = conn.cursor(cursor_factory=RealDictCursor)
        if duration is not None:
            cur.execute("""
    SELECT
        id,
        creationdate,
        viewcount,
        lasteditdate,
        lastactivitydate,
        title,
        closeddate,
        ROUND(EXTRACT(EPOCH FROM (closeddate - creationdate)) / 60, 2) AS duration
    FROM
        posts
    WHERE
        closeddate IS NOT NULL
        AND EXTRACT(EPOCH FROM (closeddate - creationdate)) / 60 <= %s
    ORDER BY
        creationdate DESC
    LIMIT
        %s;
            """, (duration, limit))

            posts_data = cur.fetchall()
            cur.close()
            conn.close()
            return {"items": posts_data}

        elif query is not None:
            normalized_query = unidecode(query).lower()

            like_query = f"%{normalized_query}%"
            cur.execute("""
            SELECT
                p.id,
                p.creationdate,
                p.viewcount,
                p.lasteditdate,
                p.lastactivitydate,
                p.title,
                p.body,
                p.answercount,
                p.closeddate,
                ARRAY_AGG(t.tagname) AS tags
            FROM
                posts p
            JOIN
                post_tags pt ON p.id = pt.post_id
            JOIN
                tags t ON pt.tag_id = t.id
            WHERE
                (LOWER(UNACCENT(p.title)) LIKE %s OR
                LOWER(UNACCENT(p.body)) LIKE %s)
            GROUP BY
                    p.id, p.creationdate, p.viewcount, p.lasteditdate, p.lastactivitydate,
                    p.title, p.body, p.answercount, p.closeddate
            ORDER BY
                p.creationdate DESC
            LIMIT
                %s;
                    """, (like_query, like_query, limit))

            posts_data = cur.fetchall()
            cur.close()
            conn.close()
            return {"items": posts_data}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

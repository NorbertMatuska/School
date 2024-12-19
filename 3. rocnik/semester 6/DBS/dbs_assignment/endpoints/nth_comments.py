from fastapi import APIRouter, HTTPException, Query, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v3/tags/{tag_name}/comments/{position}")
def get_tagged_comments(tag_name: str = Path(..., description="The name of the tag"),
                        position: int = Path(..., description="The rank position of the comment within its post"),
                        limit: int = Query(1, description="How many items to return")):
    try:
        conn = psycopg2.connect(
            host=settings.DATABASE_HOST,
            database=settings.DATABASE_NAME,
            user=settings.DATABASE_USER,
            password=settings.DATABASE_PASSWORD,
            port=settings.DATABASE_PORT
        )
        cur = conn.cursor(cursor_factory=RealDictCursor)

        cur.execute("""
        SELECT
            sub.body,
            sub.displayname,
            sub.id,
            sub.position,
            sub.score,
            sub.text,
            sub.creationdate
        FROM (
            SELECT
                p.id as post_id,
                c.id as id,
                u.displayname,
                p.body as body,
                c.text as text,
                c.score,
                p.creationdate,
                ROW_NUMBER() OVER (PARTITION BY p.id ORDER BY c.creationdate ASC) as position
            FROM
                comments c
            JOIN
                posts p ON p.id = c.postid
            JOIN
                users u ON u.id = c.userid
            JOIN
                post_tags pt ON p.id = pt.post_id
            JOIN
                tags t ON pt.tag_id = t.id
            WHERE
                t.tagname = %s
        ) sub
        WHERE
            sub.position = %s
        ORDER BY
            sub.creationdate ASC
        LIMIT %s;
        """, (tag_name, position, limit))

        comments_data = cur.fetchall()
        cur.close()
        conn.close()
        return {"items": comments_data}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

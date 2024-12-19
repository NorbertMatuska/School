from fastapi import APIRouter, HTTPException, Query, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v3/posts/{post_id}")
def get_related_posts(post_id: int = Path(..., description="The post ID"),
                      limit: int = Query(5, description="How many items to return")):
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
            u.displayname,
            p.body,
            p.creationdate as created_at
        FROM
            posts p
        JOIN
            users u ON p.owneruserid = u.id
        WHERE
            p.id = %s OR p.parentid = %s
        ORDER BY
            p.creationdate ASC
        LIMIT %s;
        """, (post_id, post_id, limit))

        posts_data = cur.fetchall()
        cur.close()
        conn.close()
        return {"items": posts_data}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

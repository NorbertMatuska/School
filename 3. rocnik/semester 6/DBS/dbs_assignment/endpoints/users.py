from fastapi import APIRouter, HTTPException, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v2/posts/{post_id}/users")
def get_users_by_post(post_id: int = Path(..., title="ID of a post")):
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
            u.id,
            u.reputation,
            u.creationdate,
            u.displayname,
            u.lastaccessdate,
            u.websiteurl,
            u.location,
            u.aboutme,
            u.views,
            u.upvotes,
            u.downvotes,
            u.profileimageurl,
            u.age,
            u.accountid
        FROM
            users u
        INNER JOIN comments c ON u.id = c.userid
        WHERE
            c.postid = %s
        ORDER BY
            c.creationdate DESC
        """, (post_id,))

        users_data = cur.fetchall()
        cur.close()
        conn.close()
        return {"items": users_data}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

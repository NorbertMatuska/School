from fastapi import APIRouter, HTTPException, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v2/users/{user_id}/friends")
def get_user_friends(user_id: int = Path(..., description="The user ID")):
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
        WHERE
            EXISTS (
                SELECT 1
                FROM comments c
                INNER JOIN posts p ON c.postid = p.id
                WHERE (p.owneruserid = %s OR c.userid = %s)
                AND u.id = c.userid
            )
        ORDER BY
            u.creationdate;
        """, (user_id, user_id))

        friends_data = cur.fetchall()
        cur.close()
        conn.close()
        return {"items": friends_data}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

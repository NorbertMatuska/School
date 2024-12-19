from fastapi import APIRouter, HTTPException, Query, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v3/tags/{tag}/comments")
def get_tagged_comments_details(tag: str = Path(..., description="The tag name"),
                                count: int = Query(40, description="Minimum number of comments to include a post")):
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
            TO_CHAR('00:00:00'::time + (comments_data.sum_diff / comments_data.count_diff) * '1 second'::interval, 'HH24:MI:SS.US') AS avg,
            comments_data.created_at,
            comments_data.diff,
            comments_data.displayname,
            comments_data.post_created_at,
            comments_data.post_id,
            comments_data.text,
            comments_data.title
        FROM (
            SELECT
                post_data.post_id,
                post_data.title,
                post_data.displayname,
                post_data.text,
                post_data.post_created_at,
                post_data.created_at,
                TO_CHAR(post_data.created_at - LAG(post_data.created_at) OVER (
                    PARTITION BY post_data.post_id ORDER BY post_data.created_at
                ), 'HH24:MI:SS.US') AS diff,
                SUM(post_data.diff) OVER (
                    PARTITION BY post_data.post_id ORDER BY post_data.created_at
                    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
                ) as sum_diff,
                COUNT(post_data.diff) OVER (
                    PARTITION BY post_data.post_id ORDER BY post_data.created_at
                    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
                ) as count_diff
            FROM (
                SELECT
                    posts.id AS post_id,
                    posts.title,
                    users.displayname,
                    comments.text,
                    posts.creationdate AS post_created_at,
                    comments.creationdate AS created_at,
                    EXTRACT(EPOCH FROM (comments.creationdate - LAG(comments.creationdate) OVER (
                        PARTITION BY comments.postid ORDER BY comments.creationdate
                    ))) AS diff
                FROM
                    comments
                JOIN
                    posts ON comments.postid = posts.id
                JOIN
                    users ON comments.userid = users.id
                JOIN
                    post_tags ON posts.id = post_tags.post_id
                JOIN
                    tags ON post_tags.tag_id = tags.id
                WHERE
                    tags.tagname = %s
            ) AS post_data
            JOIN (
                SELECT
                    postid
                FROM
                    comments
                GROUP BY
                    postid
                HAVING
                    COUNT(*) > %s
            ) AS popular_posts ON post_data.post_id = popular_posts.postid
            WHERE
                post_data.diff IS NOT NULL
        ) AS comments_data
        ORDER BY
            comments_data.post_id, comments_data.created_at;
        """, (tag, count))

        comments_details = cur.fetchall()
        cur.close()
        conn.close()
        return {"items": comments_details}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

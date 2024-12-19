from fastapi import APIRouter, HTTPException, Path
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor

router = APIRouter()


@router.get("/v2/tags/{tagname}/stats")
def get_tag_stats(tagname: str = Path(..., description="The name of the tag to retrieve stats for")):
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
WITH PostDay AS (
    SELECT
        EXTRACT(DOW FROM p.creationdate) AS day_of_week,
        COUNT(DISTINCT p.id) AS day_count_tag
    FROM posts p
    JOIN post_tags pt ON p.id = pt.post_id
    JOIN tags t ON pt.tag_id = t.id
    WHERE t.tagname = %s
    GROUP BY day_of_week
),
TotalPosts AS (
    SELECT
        EXTRACT(DOW FROM p.creationdate) AS day_of_week,
        COUNT(DISTINCT p.id) AS day_count
    FROM posts p
    JOIN post_tags pt ON p.id = pt.post_id
    JOIN tags t ON pt.tag_id = t.id
    GROUP BY day_of_week
)
SELECT
    CASE
        WHEN pd.day_of_week = 0 THEN 'sunday'
        WHEN pd.day_of_week = 1 THEN 'monday'
        WHEN pd.day_of_week = 2 THEN 'tuesday'
        WHEN pd.day_of_week = 3 THEN 'wednesday'
        WHEN pd.day_of_week = 4 THEN 'thursday'
        WHEN pd.day_of_week = 5 THEN 'friday'
        WHEN pd.day_of_week = 6 THEN 'saturday'
    END AS day,
    ROUND((pd.day_count_tag::NUMERIC/tp.day_count::NUMERIC) * 100, 2) AS day_percentage
FROM PostDay pd
JOIN TotalPosts tp ON tp.day_of_week = pd.day_of_week
ORDER BY pd.day_of_week;
        """, (tagname,))

        stats_data = cur.fetchall()
        cur.close()
        conn.close()

        stats_result = {"result": {day['day']: day['day_percentage'] for day in stats_data}}
        return stats_result

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

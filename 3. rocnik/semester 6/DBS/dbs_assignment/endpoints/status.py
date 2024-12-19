from fastapi import APIRouter, HTTPException
from dbs_assignment.config import settings
import psycopg2
from psycopg2.extras import RealDictCursor


router = APIRouter()


@router.get("/v1/status")
def status():
    #return {
    #    "DB_HOST": settings.DB_HOST,
    #    "DB_PORT": settings.DB_PORT,
    #    "DB_USER": settings.DB_USER,
    #    "DB_PASSWORD": settings.DB_PASSWORD,
    #    "DB_NAME": settings.DB_NAME
    # }
    try:
        conn = psycopg2.connect(
            host=settings.DATABASE_HOST,
            database=settings.DATABASE_NAME,
            user=settings.DATABASE_USER,
            password=settings.DATABASE_PASSWORD,
            port=settings.DATABASE_PORT)
        cur = conn.cursor(cursor_factory=RealDictCursor)

        cur.execute("SELECT version();")
        db_version = cur.fetchone()
        cur.close()
        conn.close()
        # hmmaaaaa
        return {"version": db_version['version']}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

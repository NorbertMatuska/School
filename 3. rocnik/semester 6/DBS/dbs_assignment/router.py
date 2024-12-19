from fastapi import APIRouter

from dbs_assignment.endpoints import hello
from dbs_assignment.endpoints import status
from dbs_assignment.endpoints import friends
from dbs_assignment.endpoints import stats
from dbs_assignment.endpoints import limit_posts
from dbs_assignment.endpoints import users
from dbs_assignment.endpoints import thread_posts
from dbs_assignment.endpoints import nth_comments
from dbs_assignment.endpoints import count_comments

router = APIRouter()
router.include_router(hello.router, tags=["hello"])
router.include_router(status.router, tags=["status"])
router.include_router(friends.router, tags=["friends"])
router.include_router(stats.router, tags=["stats"])
router.include_router(limit_posts.router, tags=["limit_posts"])
router.include_router(users.router, tags=["users"])
router.include_router(thread_posts.router, tags=["thread_posts"])
router.include_router(nth_comments.router, tags=["nth_comments"])
router.include_router(count_comments.router, tags=["count_comments"])

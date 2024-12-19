from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    class Config:
        case_sensitive = True

    NAME: str
    DATABASE_HOST: str
    DATABASE_PORT: str
    DATABASE_USER: str
    DATABASE_PASSWORD: str
    DATABASE_NAME: str


settings = Settings()

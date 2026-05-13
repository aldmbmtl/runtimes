import os
from fastapi import FastAPI
from fastapi.responses import RedirectResponse
import uvicorn

app = FastAPI(
    docs_url=os.environ.get("PREFIX", "/") + "docs",
)


@app.get(os.environ.get("PREFIX", "/"))
def root():
    return RedirectResponse(url=f"{prefix}docs")


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8080)

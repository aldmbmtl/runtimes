import os
from fastapi import FastAPI
from fastapi.responses import RedirectResponse
import uvicorn

prefix = os.environ.get("PREFIX", "/")
app = FastAPI(root_path=prefix, redirect_slashes=False)


@app.get("/")
def root():
    return RedirectResponse(url=f"{prefix}docs")


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8080)

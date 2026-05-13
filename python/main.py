import os
from fastapi import FastAPI
import uvicorn

prefix = os.environ.get("PREFIX", "/")
app = FastAPI(root_path=prefix, redirect_slashes=False)


@app.get("/")
def root():
    return {"status": "ok", "runtime": "python"}


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8080)

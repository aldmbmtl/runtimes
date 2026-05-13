package main

import (
	"fmt"
	"net/http"
	"os"
)

const htmlTemplate = `<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Juno — Go Runtime</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@300;400;500;700&display=swap" rel="stylesheet">
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }
    body {
      background: #0e0e10;
      color: #f2f2f3;
      font-family: 'Montserrat', sans-serif;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
    }
    .card {
      background: #1b1b1e;
      border: 1px solid #2e2e33;
      border-radius: 16px;
      padding: 48px 56px;
      max-width: 520px;
      width: 100%%;
    }
    .brand {
      display: flex;
      align-items: center;
      gap: 10px;
      margin-bottom: 40px;
    }
    .brand-dot {
      width: 10px;
      height: 10px;
      border-radius: 50%%;
      background: #f4a61d;
    }
    .brand-name {
      font-size: 14px;
      font-weight: 500;
      color: #9a9aa3;
      letter-spacing: 0.08em;
      text-transform: uppercase;
    }
    h1 {
      font-size: 32px;
      font-weight: 700;
      color: #f2f2f3;
      line-height: 1.2;
      margin-bottom: 12px;
    }
    h1 span { color: #f4a61d; }
    h2 {
      font-size: 16px;
      font-weight: 400;
      color: #9a9aa3;
      margin-bottom: 32px;
      line-height: 1.5;
    }
    .divider {
      border: none;
      border-top: 1px solid #2e2e33;
      margin-bottom: 28px;
    }
    .status {
      display: flex;
      align-items: center;
      gap: 10px;
      font-size: 13px;
      color: #9a9aa3;
    }
    .status-dot {
      width: 8px;
      height: 8px;
      border-radius: 50%%;
      background: #34d583;
      flex-shrink: 0;
    }
  </style>
</head>
<body>
  <div class="card">
    <div class="brand">
      <div class="brand-dot"></div>
      <span class="brand-name">Juno</span>
    </div>
    <h1>Hello from <span>Juno!</span></h1>
    <h2>This is the <strong>%s</strong> runtime.</h2>
    <hr class="divider">
    <div class="status">
      <div class="status-dot"></div>
      Runtime is healthy and ready to serve your application.
    </div>
  </div>
</body>
</html>`

func main() {
	prefix := os.Getenv("PREFIX")
	if prefix == "" {
		prefix = "/"
	}

	mux := http.NewServeMux()
	mux.HandleFunc(prefix, func(w http.ResponseWriter, r *http.Request) {
		if r.URL.Path != prefix {
			http.NotFound(w, r)
			return
		}
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		fmt.Fprintf(w, htmlTemplate, "Go")
	})

	http.ListenAndServe(":8080", mux)
}

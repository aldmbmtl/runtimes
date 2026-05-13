package main

import (
	"encoding/json"
	"net/http"
	"os"
)

func main() {
	prefix := os.Getenv("PREFIX")
	if prefix == "" {
		prefix = "/"
	}

	mux := http.NewServeMux()
	mux.HandleFunc(prefix, func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]string{"status": "ok", "runtime": "go"})
	})

	http.ListenAndServe(":8080", mux)
}

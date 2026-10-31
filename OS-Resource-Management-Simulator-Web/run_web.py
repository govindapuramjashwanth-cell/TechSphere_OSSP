#!/usr/bin/env python3
"""Local web server for the OS Resource Management Simulator dashboard."""
from http.server import ThreadingHTTPServer, SimpleHTTPRequestHandler
from pathlib import Path
import webbrowser

ROOT = Path(__file__).resolve().parent / "web"
PORT = 8000

class Handler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(ROOT), **kwargs)

if __name__ == "__main__":
    url = f"http://localhost:{PORT}/"
    print(f"OS Resource Management Simulator: {url}")
    print("Press Ctrl+C to stop the server.")
    try:
        webbrowser.open(url)
    except Exception:
        pass
    ThreadingHTTPServer(("127.0.0.1", PORT), Handler).serve_forever()

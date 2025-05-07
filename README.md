# Smart Response XE Web Polling App

## Structure
- `backend/` – C++ REST API server (wraps SMART Response SDK)
- `frontend/` – React web app

## Setup

### Backend
1. Download `cpp-httplib` and place `httplib.h` in `backend/` (see comment in file).
2. Build backend with CMake or MSVC, linking against `SMARTResponseSDK.dll` and including `headers/`.
3. Run backend: `./backend`

### Frontend
1. `cd frontend`
2. `npm install`
3. `npm start`

---

## Next Steps
- Fill in backend logic to call SDK functions for poll start/stop/results.
- Expand frontend for custom poll types, live updates, etc.

---

This scaffold gets you started for a web-based polling app using the SMART Response XE SDK.

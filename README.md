# Automatic Stock — Automated Warehouse

This repository contains the Automatic Stock project (PR2 — Industrial Informatics & Robotics). It implements a prototype automated warehouse: order handling, box placement algorithms for a cobot, a lightweight backend API, web frontend, and ESP32 / MQTT integration for device communications and simulation with RoboDK.

--

Quick summary:

- Domain: automated warehouse, box placement and container management for a cobot.
- Tech: C++ (algorithms & simulation), Node.js (Express backend), Web (HTML/CSS/JS), ESP32 (firmware & MQTT), RoboDK (robot simulation).

Key achievements:

- Placement and container management algorithms (C++ code in `src/`).
- Lightweight REST API in `APP/backend` (Express + `pg`) to persist orders/targets.
- Web frontend in `APP/frontend/Web` providing a cart UI and order flow.
- JSON/MQTT message formats and examples for ESP32 communication (see `Comunicaciones_ESP32-S3/formatosJSON.txt`).
- RoboDK integration for simulating target assignment and verifying robot trajectories.

--

Contents

- Architecture (text description)
- Quick install
- Usage
- File map (important folders)
- Data flow (ASCII)
- Development notes & box sizes
- Next steps & suggestions
- Credits

--

Architecture (text-based)

The system is composed of several cooperating layers and components. Mermaid diagrams were avoided due to a known rendering issue in the architecture generator; the structure is described below in plain text.

- User / Browser:
  - Interacts with the Web frontend (`APP/frontend/Web`) to create carts and place orders.

- Frontend Web:
  - Static pages (`index.html`, `carrito.html`) and JS modules (`js/` folder) that prepare order data and call backend APIs.

- Backend API (`APP/backend`):
  - An Express server that exposes REST endpoints to receive orders, persist them (via PostgreSQL), and expose computed targets for the cobot.

- Database (optional):
  - PostgreSQL (recommended) to store orders, inventory, and generated targets. The backend currently uses the `pg` client; add SQL schema or docker-compose to spin up the DB.

- ESP32 devices / MQTT:
  - Embedded devices publish/subscribe JSON messages (format examples in `Comunicaciones_ESP32-S3/formatosJSON.txt`) to inform about sensor data, confirmations, or to receive target assignments.

- RoboDK / Simulation:
  - The backend can send target sets to RoboDK for simulation and verification. RoboDK projects and robot models are in the `RoboDK/` folder.

How components interact (simplified):

1. User builds an order in the Browser → Frontend gathers items and POSTs order to Backend.
2. Backend validates order, stores it (DB), runs placement algorithm (C++/or internal module) to compute target positions.
3. Backend persists targets and notifies devices (ESP32) via MQTT or provides targets to RoboDK for simulation.
4. ESP32 receives instructions and confirms execution back to Backend via MQTT JSON messages.

--

Quick install

Requirements: `node` (v16+ recommended), `npm`, and optionally a local Postgres instance.

Backend (development):

```bash
cd APP/backend
npm install
# Run in dev mode (uses nodemon):
npm run dev
```

Frontend (static):

```bash
cd APP/frontend/Web
# You can open `index.html` in a browser, or run a simple static server:
python3 -m http.server 5500
# Then open: http://localhost:5500/index.html
```

--

Usage notes

- Open the frontend (`APP/frontend/Web/index.html`) to create and submit orders.
- The frontend JS files that handle order submission are `APP/frontend/Web/js/pedido_a_BBDD.js` and `APP/frontend/Web/js/cartService.js`.
- Start the backend to accept requests and to compute/persist targets.

Data & message formats

- MQTT / JSON message examples are available in `Comunicaciones_ESP32-S3/formatosJSON.txt`.

--

File map (high level)

- `APP/backend/` — Node.js API (Express) and dev script `npm run dev`.
- `APP/frontend/Web/` — Web UI (HTML/CSS/JS) and resources.
- `Comunicaciones_ESP32-S3/` — ESP32 code, examples and JSON formats.
- `ESP32-S3_MASTER/` — Firmware sketches and headers.
- `src/` and `headers/` — C++ algorithm implementations used for placement and container management.
- `RoboDK/` — Simulation projects, robot definitions and scene assets.

--

Data flow (ASCII)

User -> Frontend -> Backend -> Database
                     ^
                     |
                  ESP32 (MQTT)
                     |
                  RoboDK (simulation)

--

Development notes & box sizes

- Important C++ files implementing algorithms: `src/Algorithms.cpp`, `src/container.cpp`, `src/order.cpp`.
- Box sizes noted in `notes.txt` (used for packing/placement heuristics):
  - S: 150 x 120 x 100
  - M: 200 x 210 x 70
  - L: 200 x 210 x 210
  - XL: 250 x 300 x 210

Color hints (visualization): carton `#a58a67`, logo `#013357`.

--

Commands & quick helpers

```bash
# Start backend dev server
cd APP/backend && npm run dev

# Serve frontend locally
cd APP/frontend/Web && python3 -m http.server 5500

# Find algorithm sources (macOS/Linux)
grep -R "Algorithms" src/ || rg "Algorithms" src/
```

--

Next steps & suggestions

- Add a `docker-compose.yml` to bring up Postgres + backend quickly for reproducible development.
- Document backend endpoints (`APP/backend/src/index.js`) with example `curl` commands or an OpenAPI spec.
- Add unit tests for C++ placement algorithms and a small integration test for the backend endpoints.
- Add a `/docs/screenshots` folder and include UI screenshots referenced from the README.

--

Credits

- Project and code by `gonzalomaartinpenalba` (PR2 course work). See repository folders for authorship of subcomponents.

If you want, I can now:

- Add screenshots and reference them from the README.
- Generate a `docker-compose.yml` for Postgres + backend.
- Produce an OpenAPI spec (basic) from the backend routes.

Tell me which of these you'd like me to do next.

Proyect for PR2 Informática industrial y robótica.

Desarrollo de un almacen automatizado
Creación he implementación para algoritmo de colocación de cajas automáticas.

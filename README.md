# Automatic Stock — Almacén Automatizado

Una solución de proyecto para PR2 (Informática Industrial y Robótica) que implementa un sistema de gestión de pedidos, asignación de targets para un cobot (RoboDK / ESP32) y una interfaz web para pedidos y simulación.

---

**Resumen rápido:**

- **Dominio:** Almacén automatizado, colocación de cajas por Cobot, integración web y comunicaciones MQTT.
- **Lenguajes / Plataformas:** C++ (simulación / algoritmos), Node.js (API), Web (HTML/CSS/JS), ESP32 (firmware / MQTT), RoboDK (simulación robótica).

**Logros y características principales**

- Algoritmos de colocación y gestión de contenedores y cajas (implementados en `src/`).
- API REST ligera en `APP/backend` (Express + PostgreSQL client) para almacenar/recuperar pedidos y targets.
- Frontend web en `APP/frontend/Web` con carrito y flujo de pedido (`carrito.html`, `index.html`).
- Soporte de mensajes MQTT / JSON entre ESP32 y back-end (carpetas `Comunicaciones_ESP32-S3`, `ESP32-S3_MASTER`, etc.).
- Integración conceptual con RoboDK (simulación y generación de targets / trayectorias).

---

**Índice**

- [Arquitectura](#arquitectura)
- [Instalación Rápida](#instalaci%C3%B3n-r%C3%A1pida)
- [Uso](#uso)
- [Mapa de archivos](#mapa-de-archivos)
- [Diagrama de flujo de datos](#diagrama-de-flujo-de-datos)
- [Desarrollo](#desarrollo)
- [Próximos pasos y mejoras](#pr%C3%B3ximos-pasos-y-mejoras)
- [Autores y Créditos](#autores-y-cr%C3%A9ditos)

---

## Arquitectura

```mermaid
flowchart LR
  Browser[Usuario / Navegador]
  Frontend[Frontend Web<br/>`APP/frontend/Web`]
  Backend[Backend Node.js<br/>`APP/backend`]
  DB[(Postgres / BBDD)]
  ESP32[ESP32 Devices<br/>(MQTT)]
  RoboDK[RoboDK / Simulación]

  Browser -->|HTTP| Frontend
  Frontend -->|AJAX / Fetch| Backend
  Backend -->|SQL| DB
  ESP32 -->|MQTT JSON| Backend
  Backend -->|Targets / Orders| RoboDK
  RoboDK -->|Simulation results| Backend

  classDef hw fill:#ffe4b5,stroke:#b36b00;
  class ESP32,RoboDK hw;
```

> Nota: Si tu entorno no renderiza Mermaid, ver la sección 'Diagrama de flujo de datos' para un diagrama ASCII alternativo.

---

## Instalación rápida

Requisitos: `node` (v16+ recomendado), `npm`, un servidor Postgres si quieres persistencia real.

### Backend

```bash
cd APP/backend
npm install
# Inicia en modo desarrollo (usa nodemon):
npm run dev
```

### Frontend

```bash
cd APP/frontend/Web
# No hay dependencias definidas; puedes abrir `index.html` directamente
# O servir con un servidor estático (recomendado para CORS):
python3 -m http.server 5500
# Después abre: http://localhost:5500/index.html
```

---

## Uso

- Abrir la interfaz web (`APP/frontend/Web/index.html`) para navegar y simular pedidos.
- El carrito y pedido envían las peticiones al backend (ver `APP/frontend/Web/js/pedido_a_BBDD.js`, `cartService.js`).
- El backend expone endpoints en `APP/backend/src/index.js` (iniciar el servidor para ver rutas). Para desarrollo, ejecuta `npm run dev`.

### Peticiones y formato

- Mensajes MQTT / JSON: el proyecto maneja JSON para la comunicación entre ESP32 y servidor. Ver `Comunicaciones_ESP32-S3/formatosJSON.txt` para ejemplos de formatos.

---

## Mapa de archivos (resumen relevante)

- `APP/backend/` — API (Express + PG client). Script dev: `npm run dev`.
- `APP/frontend/Web/` — Interfaz web, CSS y scripts (`index.html`, `carrito.html`, `js/*.js`).
- `Comunicaciones_ESP32-S3/` — Código y recursos relacionados con ESP32 (MQTT, ejemplos). 
- `ESP32-S3_MASTER/` — Firmware, cabeceras y sketches de ejemplo.
- `src/` y `headers/` — Implementación C++ de algoritmos, cajas, contenedores, order handling, MQTT helpers (uso en simulaciones y RoboDK).
- `RoboDK/` — Proyectos y recursos para simulación (archivos `.rdk`, robots y elementos 3D).

---

## Diagrama de flujo de datos (ASCII)

Browser -> Frontend -> Backend -> DB
           ^                 |
           |                 v
        ESP32 (MQTT) ---> Backend -> RoboDK

---

## Desarrollo y notas técnicas

- Algoritmos principales para colocar cajas: implementaciones en `src/` (`Algorithms.cpp`, `container.cpp`, `order.cpp`).
- Formatos y tamaños de cajas (desde `notes.txt`):
  - S: 150×120×100
  - M: 200×210×70
  - L: 200×210×210
  - XL: 250×300×210

- Si se usa RoboDK, los targets se generan desde el backend y se comunican a RoboDK para simulación y verificación de trayectorias.

### Comandos útiles

```bash
# Iniciar backend (desarrollo)
cd APP/backend && npm run dev

# Servir frontend (desde Web folder)
cd APP/frontend/Web && python3 -m http.server 5500

# Buscar archivos C++ relacionados con algoritmos
rg "Algorithms" src/ || grep -R "Algorithms" src/ 
```

---

## Próximos pasos y mejoras sugeridas

- Documentar los endpoints REST en `APP/backend/src/index.js` con ejemplos `curl`.
- Añadir un `README` detallado en `APP/backend` y en `APP/frontend/Web` con instrucciones para testeo y despliegue.
- Incluir script de inicialización SQL o `docker-compose` para levantar Postgres y el backend de forma reproducible.
- Añadir tests unitarios para los algoritmos de colocación (`src/`), y CI básico.

---

## Autores y créditos

- Proyecto y código por el equipo del PR2 / autor: `gonzalomaartinpenalba`.

---

Si quieres, puedo:

- Añadir imágenes o capturas de pantalla dentro del repo (`/docs/screenshots`) y referenciarlas en este README.
- Generar un `docker-compose.yml` para levantar backend+Postgres.
- Documentar las rutas REST con ejemplos `curl` y OpenAPI minimal.

Dime qué prefieres que haga a continuación.
Proyect for PR2 Informática industrial y robótica.

Desarrollo de un almacen automatizado
Creación he implementación para algoritmo de colocación de cajas automáticas.

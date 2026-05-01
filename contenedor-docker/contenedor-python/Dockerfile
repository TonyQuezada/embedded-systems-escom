# ── Imagen base ───────────────────────────────────────────────
FROM python:3.11-slim

LABEL maintainer="Estudiante IoT"
LABEL description="Contenedor adicional: genera grafica PNG de sensores IoT con Python/matplotlib."
LABEL version="1.0"

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY generar_grafica.py .
RUN mkdir -p /output

CMD ["python3", "generar_grafica.py"]

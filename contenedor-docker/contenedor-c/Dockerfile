# ── Imagen base (igual que el repositorio del profesor) ───────
FROM ubuntu:22.04

LABEL maintainer="Estudiante IoT"
LABEL description="Compila un programa C++ que genera datos y usa gnuplot para producir un JPG."
LABEL version="1.0"

ENV DEBIAN_FRONTEND=noninteractive

# ── Herramientas (igual que el README del profesor) ───────────
RUN apt-get -o Acquire::Check-Valid-Until=false \
            -o Acquire::Check-Date=false \
            update && apt-get install -y \
        build-essential \
        g++ \
        gnuplot \
        xdg-utils \
        libx11-dev \
    && rm -rf /var/lib/apt/lists/*

# ── Directorio de trabajo ──────────────────────────────────────
WORKDIR /usr/src/app

# ── Copiar fuentes ─────────────────────────────────────────────
COPY main.cpp Makefile ./

# ── Crear directorio de salida ─────────────────────────────────
RUN mkdir -p /output

# ── Argumento de construcción para el target de make ──────────
ARG MAKE_TARGET=all
ENV TARGET=${MAKE_TARGET}

# ── Comando igual al del README del profesor ───────────────────
CMD make ${TARGET}

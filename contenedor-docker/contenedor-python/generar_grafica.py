#!/usr/bin/env python3
"""
generar_grafica.py
Simula datos de sensores IoT durante 24 horas y genera una grafica PNG
usando matplotlib. Contenedor adicional propuesto para la tarea.
"""
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import os

OUTPUT_DIR  = "/output"
OUTPUT_FILE = os.path.join(OUTPUT_DIR, "grafica_sensores.png")

def main():
    print("=== Generador de Grafica de Sensores IoT (Python) ===")
    horas = np.arange(0, 24, 1)
    np.random.seed(42)
    temperatura = 22 + 5*np.sin((horas-6)*np.pi/12) + np.random.normal(0, 0.4, 24)
    humedad     = 60 - 10*np.sin((horas-8)*np.pi/12) + np.random.normal(0, 1.0, 24)
    luminosidad = np.clip(
        80*np.sin(np.pi*(horas-6)/12)*(horas>=6)*(horas<=18), 0, None
    ) + np.random.normal(0, 2, 24)

    fig, axes = plt.subplots(3, 1, figsize=(12, 9), sharex=True)
    fig.patch.set_facecolor('#1a1a2e')
    fig.suptitle('Dashboard de Sensores IoT - Lecturas de 24 horas',
                 fontsize=15, fontweight='bold', color='white', y=0.98)

    config = [
        ('Temperatura (C)',    temperatura, '#ff6b6b', (15, 32)),
        ('Humedad (%)',        humedad,     '#4ecdc4', (40, 80)),
        ('Luminosidad (lux)', luminosidad, '#ffe66d', (-5, 100)),
    ]

    for ax, (label, dato, color, ylim) in zip(axes, config):
        ax.set_facecolor('#16213e')
        ax.plot(horas, dato, color=color, linewidth=2.5, zorder=3)
        ax.fill_between(horas, dato, alpha=0.25, color=color)
        ax.set_ylabel(label, color='white', fontsize=10)
        ax.set_ylim(ylim)
        ax.tick_params(colors='white')
        ax.grid(True, alpha=0.2, color='white', linestyle='--')
        for spine in ax.spines.values():
            spine.set_edgecolor('#4a4a8a')
        promedio = np.mean(dato)
        ax.axhline(promedio, color='white', linestyle=':', linewidth=1.2, alpha=0.6)
        ax.text(23.2, promedio, f'avg\n{promedio:.1f}', color='white',
                fontsize=7, va='center', alpha=0.8)

    axes[-1].set_xlabel('Hora del dia (h)', color='white', fontsize=10)
    axes[-1].set_xticks(range(0, 24, 2))
    axes[-1].tick_params(colors='white')

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    plt.savefig(OUTPUT_FILE, dpi=150, bbox_inches='tight',
                facecolor=fig.get_facecolor())
    plt.close()
    print(f"Grafica guardada en: {OUTPUT_FILE}")
    print("Proceso completado correctamente.")

if __name__ == "__main__":
    main()

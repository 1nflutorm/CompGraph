import numpy as np
import matplotlib.pyplot as plt

# Ввод данных с клавиатуры
U001 = float(input("Введите значение напряжения смещения нейтрали относительно земли U001: "))
Ua01 = float(input("Введите значение напряжения фазы A относительно земли Ua01: "))
Ub01 = float(input("Введите значение напряжения фазы B относительно земли Ub01: "))
Uc01 = float(input("Введите значение напряжения фазы C относительно земли Uc01: "))
Uh = float(input("Введите значение напряжения прикосновения Uh: "))

# Углы для фаз A, B и C, чтобы Ua смотрела вверх, Uc влево, и Ub вправо
angles = np.deg2rad([90, 210, 330])

# Задаем фазы A, B и C с углами 90°, 210° и 330°
phasors = np.array([np.exp(1j * angle) for angle in angles])

# Смещенная нейтраль относительно земли
neutral_shift = U001 * np.exp(1j * np.pi)  # Смещение нейтрали (по оси Y)

# Координаты точек земли для каждой фазы с учетом смещения нейтрали
ground_points = [
    phasor + Ua01 * np.exp(1j * np.angle(neutral_shift - phasor)) for phasor in phasors
]

# Построение графика
fig, ax = plt.subplots()
ax.set_aspect('equal', 'box')
ax.set_xlim(-300, 300)
ax.set_ylim(-300, 300)

# Рисуем фазы (векторы Ua, Ub, Uc) без использования напряжения Uh
phase_labels = ['Ua', 'Uc', 'Ub']
for i, phasor in enumerate(phasors):
    ax.plot([0, phasor.real * 50], [0, phasor.imag * 50], marker='o')
    ax.text(phasor.real * 50 * 1.1, phasor.imag * 50 * 1.1, phase_labels[i], ha='center', va='center', color='blue')

# Рисуем напряжения относительно земли
for i, (phasor, ground) in enumerate(zip(phasors, ground_points)):
    ax.plot([phasor.real * 50, ground.real], [phasor.imag * 50, ground.imag], 'b--', label=f'U{i+1}01')
    ax.plot(ground.real, ground.imag, 'ro')  # Точка земли фазы

# Отмечаем смещение нейтрали
ax.plot([0, neutral_shift.real], [0, neutral_shift.imag], 'g--', label='U001 (Neutral Shift)')

# Отмечаем точку Uh
uh_x, uh_y = Uh * np.cos(np.pi / 4), Uh * np.sin(np.pi / 4)
ax.plot([0, uh_x], [0, uh_y], 'm--')
ax.text(uh_x * 1.1, uh_y * 1.1, 'Uh', ha='center', va='center', color='magenta')

# Настройка легенды вне диаграммы
ax.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
ax.grid(True)

# Настройки подписей и заголовка
plt.xlabel('Real Part')
plt.ylabel('Imaginary Part')
plt.title('Vector Diagram of Phase and Ground Voltages')
plt.show()
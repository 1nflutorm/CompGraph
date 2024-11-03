import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

delete = []
index = 0

#функция поворота вокруг оси x
def rotate_surface_x(X, Y, Z, angle):
    redians = np.radians(angle)
    rotation_matrix = np.array([[np.cos(redians), 0, np.sin(redians)],
                                    [0, 1, 0],
                                    [-np.sin(redians), 0, np.cos(redians)]])
    
    points = np.array([X.flatten(), Y.flatten(), Z.flatten()])
    rotated_points = rotation_matrix @ points
    X_rotated = rotated_points[0].reshape(X.shape)
    Y_rotated = rotated_points[1].reshape(Y.shape)
    Z_rotated = rotated_points[2].reshape(Z.shape)

    return X_rotated, Y_rotated, Z_rotated

#функция поворота вокруг оси у
def rotate_surface_y(X, Y, Z, angle):
    redians = np.radians(angle)
    rotation_matrix = np.array([[np.cos(redians), -np.sin(redians), 0],
                                    [np.sin(redians), np.cos(redians), 0],
                                    [0, 0, 1]])
    
    points = np.array([X.flatten(), Y.flatten(), Z.flatten()])
    rotated_points = rotation_matrix @ points
    X_rotated = rotated_points[0].reshape(X.shape)
    Y_rotated = rotated_points[1].reshape(Y.shape)
    Z_rotated = rotated_points[2].reshape(Z.shape)

    return X_rotated, Y_rotated, Z_rotated

def add_coords_to_frame(frame, entryArr):
    label = tk.Label(frame, text='x').pack(side=tk.LEFT)
    entry = tk.Entry(frame, width=20)
    entry.pack(side=tk.LEFT)
    entryArr.append(entry)

    label = tk.Label(frame, text='y').pack(side=tk.LEFT)
    entry = tk.Entry(frame, width=20)
    entry.pack(side=tk.LEFT)
    entryArr.append(entry)

    label = tk.Label(frame, text='z').pack(side=tk.LEFT)
    entry = tk.Entry(frame, width=20)
    entry.pack(side=tk.LEFT)
    entryArr.append(entry)

def draw_surface():
    x1, y1, z1 = [float(p1[0].get()), float(p1[1].get()), float(p1[2].get())]
    x2, y2, z2 = [float(p2[0].get()), float(p2[1].get()), float(p2[2].get())]
    x3, y3, z3 = [float(p3[0].get()), float(p3[1].get()), float(p3[2].get())]
    x4, y4, z4 = [float(p4[0].get()), float(p4[1].get()), float(p4[2].get())]

    x = np.linspace(min(x1, x2, x3, x4), max(x1, x2, x3, x4), 100)
    y = np.linspace(min(y1, y2, y3, y4), max(y1, y2, y3, y4), 100)
    X, Y = np.meshgrid(x, y)

    Z = (1 - (X - x1) / (x2 - x1)) * (1 - (Y - y1) / (y3 - y1)) * z1 + \
        ((X - x1) / (x2 - x1)) * (1 - (Y - y1) / (y3 - y1)) * z2 + \
        (1 - (X - x3) / (x4 - x3)) * ((Y - y1) / (y3 - y1)) * z3 + \
        ((X - x3) / (x4 - x3)) * ((Y - y1) / (y3 - y1)) * z4

    return X, Y, Z


def update_plot(X_list, Y_list, Z_list):
    global index

    if(len(delete) != 0):
        delete[index].get_tk_widget().pack_forget()
        index = index + 1

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for i in range(len(X_list)):
        ax.plot_surface(X_list[i], Y_list[i], Z_list[i], cmap='viridis', alpha=0.5)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    ax.quiver(0, 0, 0, 5, 0, 0, color='r', arrow_length_ratio=0.1)
    ax.quiver(0, 0, 0, 0, 5, 0, color='g', arrow_length_ratio=0.1)
    ax.quiver(0, 0, 0, 0, 0, 5, color='b', arrow_length_ratio=0.1)

    canvas = FigureCanvasTkAgg(fig, master=window)
    canvas.draw()
    canvas.get_tk_widget().pack()

    delete.append(canvas)
    
def draw():
    X, Y, Z = draw_surface()
    X_glob.append(X)
    Y_glob.append(Y)
    Z_glob.append(Z)
    update_plot(X_glob, Y_glob, Z_glob)

def on_rotate_x():
    angle = float(entry_angle_x.get())

    for i in range(len(X_glob)):
        X_glob[i], Y_glob[i], Z_glob[i] = rotate_surface_x(X_glob[i], Y_glob[i], Z_glob[i], angle)
    update_plot(X_glob, Y_glob, Z_glob)

def on_rotate_y():
    angle = float(entry_angle_y.get())

    for i in range(len(X_glob)):
        X_glob[i], Y_glob[i], Z_glob[i] = rotate_surface_y(X_glob[i], Y_glob[i], Z_glob[i], angle)
    update_plot(X_glob, Y_glob, Z_glob)  
  
# Создание основного окна
window = tk.Tk()
window.title("Построение билинейной поверхности")

# Фреймы для организации интерфейса
main_frame = tk.Frame(window)
main_frame.pack(side=tk.LEFT, padx=10)

# Поля ввода для координат (левая часть)
labels = ["Точка 1", "Точка 2", "Точка 3", "Точка 4"]
entries = []
point1 = tk.LabelFrame(main_frame, text='Точка 1', width=300, height=40)
point1.pack(padx=30, pady=10)
point2 = tk.LabelFrame(main_frame, text='Точка 2', width=300, height=40)
point2.pack(padx=30, pady=10)
point3 = tk.LabelFrame(main_frame, text='Точка 3', width=300, height=40)
point3.pack(padx=30, pady=10)
point4 = tk.LabelFrame(main_frame, text='Точка 4', width=300, height=40)
point4.pack(padx=30, pady=10)

p1 = []
p2 = []
p3 = []
p4 = []

add_coords_to_frame(point1, p1)
add_coords_to_frame(point2, p2)
add_coords_to_frame(point3, p3)
add_coords_to_frame(point4, p4)

X_glob = []
Y_glob = []
Z_glob = []

draw_button = tk.Button(main_frame, text="Построить билинейную поверхность", command=draw)
draw_button.pack(pady=5)

label = tk.Label(main_frame, text='Поворот отностительно X').pack()
entry_angle_x = tk.Entry(main_frame)
entry_angle_x.pack()
draw_button = tk.Button(main_frame, text="Повернуть относительно X", command=on_rotate_x)
draw_button.pack(pady=5)

label = tk.Label(main_frame, text='Поворот отностительно Y').pack()
entry_angle_y = tk.Entry(main_frame)
entry_angle_y.pack()
draw_button = tk.Button(main_frame, text="Повернуть относительно Y", command=on_rotate_y)
draw_button.pack(pady=5)

# Запуск основного цикла приложения
window.mainloop()
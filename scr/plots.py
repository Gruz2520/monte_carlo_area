import pandas as pd
import matplotlib.pyplot as plt

ranges = [0, 1, 2]
real_area = 0.944517  

for range_val in ranges:
    filename = f"../data/monte_carlo_data_{range_val}.csv"
    df = pd.read_csv(filename)

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.plot(df['N'], df['Area'], label='Приблизительная площадь', color='blue')
    plt.axhline(y=real_area, color='orange', linestyle='--', label='Реальная площадь')
    plt.xlabel('Количество точек (N)')
    plt.ylabel('Примерная площадь')
    plt.title(f'Размер квадрата в диапазоне № {range_val}')
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(df['N'], df['RelativeError'], label='Ошибка', color='blue')
    plt.axhline(y=0, color='orange', linestyle='--', label='0 Ошибка')
    plt.xlabel('Количество точек (N)')
    plt.ylabel('Ошибка')
    plt.title(f'Размер квадрата в диапазоне № {range_val}')
    plt.legend()

    plt.tight_layout()
    plt.show()

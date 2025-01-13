import matplotlib.pyplot as plt

# ts ftv55
# strategy_1 = {"time": 8, "error": 2.3}
# strategy_2 = {"time": 25, "error": 15.29}
# strategy_3 = {"time": 19, "error": 7.21}

# ts ftv170
strategy_1 = {"time": 0, "error": 22.29}
strategy_2 = {"time": 0, "error": 28.35}
strategy_3 = {"time": 0, "error": 22.76}

# ts rbg358.atsp
# strategy_1 = {"time": 7, "error": 17.7}
# strategy_2 = {"time": 0, "error": 48.9}
# strategy_3 = {"time": 48, "error": 15.39}


# Plot
plt.figure(figsize=(10, 6))
# plt.plot(time, relative_error, marker='o', label="Błąd względny")

# Add cooling rates as annotations
# for t, err, rate in zip(time, relative_error, cooling_rates):
#     plt.annotate(f"{rate}", (t, err), textcoords="offset points", xytext=(10, -10), ha='center')

plt.scatter(strategy_1["time"], strategy_1["error"], color="red", label="insert")
plt.scatter(strategy_2["time"], strategy_2["error"], color="blue", label="reverse")
plt.scatter(strategy_3["time"], strategy_3["error"], color="green", label="swap")

# Labels and title
plt.title("Wykres błędu w funkcji czasu dla najlepszego rozwiązania pliku ftv170")
plt.xlabel("Czas (s)")
plt.ylabel("Błąd względny (%)")
plt.grid(True)
plt.legend()
plt.show()

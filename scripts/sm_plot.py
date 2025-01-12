import matplotlib.pyplot as plt



# sm ftv55
# cooling_rate_1 = {"time": 21.14, "error": 7.09}
# cooling_rate_2 = {"time": 35.29, "error": 4.29}
# cooling_rate_3 = {"time": 42.77, "error": 6.59}

# sm ftv170
cooling_rate_1 = {"time": 39.19, "error": 27.5}
cooling_rate_2 = {"time": 51.3, "error": 20.68}
cooling_rate_3 = {"time": 63.76, "error": 17.68}

# sm rgb358
# cooling_rate_1 = {"time": 56.55, "error": 3.78}
# cooling_rate_2 = {"time": 78.56, "error": 3.7}
# cooling_rate_3 = {"time": 116.48, "error": 2.06}

# Plot
plt.figure(figsize=(10, 6))
# plt.plot(time, relative_error, marker='o', label="Błąd względny")

# Add cooling rates as annotations
# for t, err, rate in zip(time, relative_error, cooling_rates):
#     plt.annotate(f"{rate}", (t, err), textcoords="offset points", xytext=(10, -10), ha='center')

plt.scatter(cooling_rate_1["time"], cooling_rate_1["error"], color="red", label="0.9999999")
plt.scatter(cooling_rate_2["time"], cooling_rate_2["error"], color="blue", label="0.999999925")
plt.scatter(cooling_rate_3["time"], cooling_rate_3["error"], color="green", label="0.99999995")

# Labels and title
plt.title("Wykres błędu w funkcji czasu dla najlepszego rozwiązania pliku ftv170")
plt.xlabel("Czas (s)")
plt.ylabel("Błąd względny (%)")
plt.grid(True)
plt.legend()
plt.show()

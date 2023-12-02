import numpy as np

# Define the training data and target outputs
X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([0, 0, 0, 1])

# Initialize the weights and bias
w = np.array([0.0, 0.0])
b = 0.0
learning_rate = 0.1

# Training the perceptron
for i in range(100):  # You can adjust the number of iterations
    error = 0
    for j in range(len(X)):
        input_data = X[j]
        target = y[j]

        # Calculate the predicted output
        predicted = np.dot(w, input_data) + b

        # Update the weights and bias
        w += learning_rate * (target - predicted) * input_data
        b += learning_rate * (target - predicted)

        error += abs(target - predicted)

    # If the perceptron correctly classifies all examples, stop training
    if error == 0:
        print("Perceptron has converged.")
        break

# Print the final weights and bias
print("Final weights:", w)
print("Final bias:", b)

# Decision boundary: w1 * x1 + w2 * x2 + b = 0


# Test the trained perceptron
for j in range(len(X)):
    input_data = X[j]
    predicted = np.dot(w, input_data) + b
    print(f"Input: {input_data}, Predicted: {int(predicted > 0.5)}")


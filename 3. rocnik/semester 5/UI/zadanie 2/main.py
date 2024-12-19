import random
import math
import matplotlib.pyplot as plt


def draw_best_route(cities, best_route):
    # Extracting x and y coordinates of cities
    x_coords = [x for x, y in cities]
    y_coords = [y for x, y in cities]

    # Plotting the cities
    plt.figure(figsize=(10, 10))
    plt.scatter(x_coords, y_coords, c='red')

    # Annotating cities
    for i, (x, y) in enumerate(cities):
        plt.text(x, y, f'{i}')

    # Plotting the best route
    for i in range(len(best_route)):
        start_city = cities[best_route[i]]
        end_city = cities[best_route[(i + 1) % len(best_route)]]
        plt.plot([start_city[0], end_city[0]], [start_city[1], end_city[1]], 'b')

    # Adding titles and labels
    plt.title('Best Route')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')

    # Show or save the plot
    plt.show()
    # plt.savefig('best_route.png')  # Uncomment to save the plot as an image


number_of_cities = 20

population_size = 100

# Generating random coordinates for cities
cities = []

for _ in range(number_of_cities):
    x_coordinate = random.randint(0, 200)
    y_coordinate = random.randint(0, 200)
    city = (x_coordinate, y_coordinate)
    cities.append(city)

# cities = [(28, 61), (128, 93), (77, 44), (68, 164), (8, 197), (117, 174), (142, 156), (154, 53), (90, 194), (12, 181),
#          (27, 86), (99, 133), (165, 28), (50, 80), (85, 155), (25, 117), (172, 188), (2, 115), (83, 63), (102, 81)]


def euclidean_distance(city1, city2):
    return ((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2) ** 0.5


def calculate_total_distance(route):
    total_distance = 0
    num_cities = len(route)

    for i in range(num_cities):
        current_city = cities[route[i]]
        next_city = cities[route[(i + 1) % num_cities]]
        distance = euclidean_distance(current_city, next_city)
        total_distance += distance

    return total_distance


def calculate_fitness(route):
    return 1 / calculate_total_distance(route)


population = []

for _ in range(population_size):
    # Create a random route by shuffling the range of city indices
    random_route = random.sample(range(number_of_cities), number_of_cities)
    population.append(random_route)


def roulette_wheel(fitness_scores):
    # Calculate the total fitness of the population
    total_fitness = sum(fitness_scores)

    # Calculate the selection probability for each individual
    # This is done by dividing the fitness of each individual by the total fitness
    # Resulting in a list of probabilities that sum up to 1
    selection_probs = [f / total_fitness for f in fitness_scores]

    # Randomly select two individuals from the population
    # The selection is based on the calculated probabilities
    # So individuals with higher fitness have a higher chance of being selected
    selected_parents = random.choices(population, weights=selection_probs, k=2)

    # Return the selected parents
    return selected_parents


def tournament_selection(fitness_scores, k=5):
    winners = []

    while len(winners) < 2:
        # Select k individuals randomly
        selected_indices = random.sample(range(len(population)), k)
        selected_fitness = [fitness_scores[i] for i in selected_indices]

        # Find the individual with the highest fitness
        best_index = selected_indices[selected_fitness.index(max(selected_fitness))]

        if population[best_index] not in winners:
            winners.append(population[best_index])

    return winners


def crossover(parent1, parent2):
    size = len(parent1)
    child = [-1] * size
    start, end = sorted(random.sample(range(size), 2))
    child[start:end] = parent1[start:end]

    child_pos = end
    for gene in parent2[end:] + parent2[:end]:
        if gene not in child:
            if child_pos == size:
                child_pos = 0
            child[child_pos] = gene
            child_pos += 1

    return child


def mutate(route):
    idx1, idx2 = random.sample(range(len(route)), 2)
    route[idx1], route[idx2] = route[idx2], route[idx1]
    return route


selection_method = input("Choose a selection method:\n1 - roulette wheel selection\n2 - tournament selection\n")

highest_fitness = []
average_fitness = []
best_individual = None
best_fitness = 0

for generation in range(500):  # Number of generations
    fitness_scores = [calculate_fitness(individual) for individual in population]

    avg_fitness = sum(fitness_scores) / len(fitness_scores)
    average_fitness.append(avg_fitness)
    # Check and store the best individual and its fitness
    for i, individual in enumerate(population):
        if fitness_scores[i] > best_fitness:
            best_fitness = fitness_scores[i]
            best_individual = individual

    new_population = []
    for _ in range(population_size - 1):  # Leave space for the best individual
        if str(selection_method) == "1":
            parent1, parent2 = roulette_wheel(fitness_scores)
            child = crossover(parent1, parent2)
        elif str(selection_method) == "2":
            parent1, parent2 = tournament_selection(fitness_scores)
            child = crossover(parent1, parent2)
        else:
            print("Invalid selection method")
            break
        if random.random() < 0.1:  # Mutation probability
            child = mutate(child)
        new_population.append(child)

    # Add the best individual from the previous generation
    new_population.append(best_individual)

    population = new_population

    # Store the highest fitness from the current generation
    highest_fitness_value = max(fitness_scores)
    highest_fitness.append(highest_fitness_value)

# Finding the shortest route
best_route = min(population, key=calculate_total_distance)
best_distance = calculate_total_distance(best_route)

print("Najlepšia trasa:", best_route)
print("Dĺžka trasy:", best_distance)

# Plotting the convergence graph for genetic algorithm
plt.figure(figsize=(10, 6))
plt.plot(highest_fitness, label='Highest Fitness')
plt.plot(average_fitness, label='Average Fitness')
plt.xlabel('Generation')
plt.ylabel('Fitness')
plt.title('Convergence of Genetic Algorithm Over Generations')
plt.legend()
plt.show()

draw_best_route(cities, best_route)


# Fitness function for SA
def calculate_fitness_from_distance(distance):
    return 1 / distance


# Using Simulated Annealing
def simulated_annealing(cities):
    current_solution = random.sample(range(number_of_cities), number_of_cities)
    current_distance = calculate_total_distance(current_solution)
    sa_fitness = [calculate_fitness_from_distance(current_distance)]  # List to track fitness for convergence graph
    temperature = 1.0
    cooling_rate = 0.0003

    while temperature > 0.0001:
        new_solution = current_solution[:]
        idx1, idx2 = random.sample(range(len(cities)), 2)
        new_solution[idx1], new_solution[idx2] = new_solution[idx2], new_solution[idx1]

        new_distance = calculate_total_distance(new_solution)
        if new_distance < current_distance:
            current_solution, current_distance = new_solution, new_distance
            sa_fitness.append(calculate_fitness_from_distance(current_distance))
        else:
            if random.random() < math.exp((current_distance - new_distance) / temperature):
                current_solution, current_distance = new_solution, new_distance
                sa_fitness.append(calculate_fitness_from_distance(current_distance))

        temperature *= 1 - cooling_rate

    return current_solution, current_distance, sa_fitness


# Using Simulated Annealing
sa_best_route, sa_best_distance, sa_fitness = simulated_annealing(cities)
print("Best route (SA):", sa_best_route)
print("Route length (SA):", sa_best_distance)

# Drawing the best route from Simulated Annealing
draw_best_route(cities, sa_best_route)

# Plotting the convergence graph for Simulated Annealing
plt.figure(figsize=(10, 6))
plt.plot(sa_fitness, label='Fitness (Simulated Annealing)')
plt.xlabel('Iteration')
plt.ylabel('Fitness')
plt.title('Convergence of Simulated Annealing')
plt.legend()
plt.show()

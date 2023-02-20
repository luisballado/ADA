import numpy as np

# Definir la función de fitness a ser optimizada
def fitness_func(x):
    return np.sum(x ** 2)

# Definir la clase de la estrategia evolutiva
class EvolutionStrategy:
    def __init__(self, n_vars, mu, sigma, alpha, max_iter):
        self.n_vars = n_vars # Número de variables de decisión
        self.mu = mu # Tamaño de la población
        self.sigma = sigma # Tamaño de paso inicial
        self.alpha = alpha # Tasa de aprendizaje de la regla de actualización de sigma
        self.max_iter = max_iter # Número máximo de iteraciones

    def run(self):
        # Inicializar la población aleatoria
        population = np.random.normal(0, 1, size=(self.mu, self.n_vars))

        for i in range(self.max_iter):
            # Generar muestras aleatorias de la población actual
            samples = np.random.normal(0, 1, size=(self.mu, self.n_vars))
            samples *= self.sigma
            samples += population

            # Evaluar las muestras
            fitness = np.apply_along_axis(fitness_func, 1, samples)

            # Seleccionar los mejores miembros de la población actual
            idx = np.argsort(fitness)[:self.mu]
            population = samples[idx]

            # Actualizar sigma utilizando una regla de aprendizaje
            #self.sigma *= np.exp(self.alpha * (np.mean(np.square(samples)) - 1))
            self.sigma = np.clip(self.sigma * np.exp(self.alpha * (np.mean(np.square(samples)) - 1)), 1e-8, 1e8)
        # Retornar el mejor individuo y su fitness
        best_idx = np.argmin(np.apply_along_axis(fitness_func, 1, population))
        best_individual = population[best_idx]
        best_fitness = fitness[best_idx]
        return best_individual, best_fitness

# Parámetros de la estrategia evolutiva
n_vars = 10 # Número de variables de decisión
mu = 10 # Tamaño de la población
sigma = 0.1 # Tamaño de paso inicial
alpha = 0.03 # Tasa de aprendizaje de la regla de actualización de sigma
max_iter = 100 # Número máximo de iteraciones

# Ejecutar la estrategia evolutiva
es = EvolutionStrategy(n_vars, mu, sigma, alpha, max_iter)
best_individual, best_fitness = es.run()

# Imprimir los resultados
print("Mejor individuo:", best_individual)
print("Fitness del mejor individuo:", best_fitness)

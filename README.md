## Descripcion de la simulacion

Este proyecto es una simulacion de aventuras medievales que corre en la consola. El jugador controla a Sir Aldric, un caballero que recorre un mundo compuesto por diferentes tipos de lugares: aldeas, bosques, castillos y cuevas.

Durante el recorrido, Sir Aldric puede encontrarse con distintos personajes. Si encuentra un goblin o un mago hostil, entra en combate. Si encuentra un aldeano, puede comprarle armas o armaduras. Si encuentra un mago amistoso en una aldea, este lo cura por completo. El objetivo final es llegar a la cueva del dragon y derrotar a Ignarath el Consumidor para ganar. Si el caballero muere durante el camino, la simulacion termina en derrota.

Al finalizar la partida, el programa guarda automaticamente dos archivos: una bitacora con los eventos ocurridos y un reporte con las estadisticas finales.



## Estructura del proyecto

A continuacion se lista cada archivo del proyecto y su funcion dentro del sistema:

main.cpp: Punto de entrada del programa. Crea el mundo, el logger y arranca la simulacion.
Entity.h: Clase base de la que heredan todos los personajes. Define nombre y descripcion.
Enemy.h / Enemy.cpp: Clase de enemigo con HP, arma y armadura. Tiene metodos virtuales que sus subclases sobreescriben.
Goblin.h: Subclase de Enemy. Al morir suelta 10 de oro.
Dragon.h: Subclase de Enemy. Matarlo activa la condicion de victoria.
Mage.h: Subclase de Enemy. En aldeas es amistoso y cura al caballero. En castillos es hostil.
Knight.h / Knight.cpp: Clase del protagonista. Maneja su vida, oro, vendajes, armas y armadura.
Villager.h / Villager.cpp: Personaje no hostil que vende armas y armaduras, y regala loot si tiene suficiente stock.
Weapon.h / Weapon.cpp: Representa un arma. Usa el patron Strategy para calcular el dano segun el tipo.
DamageStrategy.h: Interfaz abstracta del patron Strategy para el calculo de dano.
SwordStrategy.h / SwordStrategy.cpp: Estrategia de espada: el dano es igual al dano base del arma.
BowStrategy.h / BowStrategy.cpp: Estrategia de arco: el dano es el dano base menos 2.
SpellStrategy.h / SpellStrategy.cpp: Estrategia de hechizo: el dano es el dano base multiplicado por 1.5, con sistema de mana.
Armor.h / Armor.cpp: Representa una armadura con nombre y porcentaje de reduccion de dano.
Room.h / Room.cpp: Representa una sala del mundo con su tipo, entidades y conexiones a otras salas.
World.h / World.cpp: Contiene todas las salas y al caballero. Se encarga de mover al caballero entre salas.
WorldLoader.h / WorldLoader.cpp: Lee los cinco archivos de entrada y construye el mundo completo.
SimulationEngine.h / SimulationEngine.cpp: Motor del juego. Controla los turnos, los encuentros aleatorios, el combate y el menu.
Logger.h / Logger.cpp: Escribe los eventos de la partida en el archivo bitacora.txt.
ReportGenerator.h / ReportGenerator.cpp: Al terminar la partida genera el archivo reporte_final.txt con el resumen.
config.txt: Archivo de configuracion con los datos iniciales del caballero y la sala de inicio.
mundo.txt: Define las salas, sus tipos y como estan conectadas entre si.
entidades.txt: Lista todos los personajes del juego con sus estadisticas.
armas_aldeanos.txt: Lista las armas que vende cada aldeano y sus precios.
armaduras_aldeanos.txt: Lista las armaduras que vende cada aldeano y sus precios.
bitacora.txt: Archivo generado por el programa al correr con el registro de eventos.
reporte_final.txt: Archivo generado por el programa al correr con el resumen final de la partida.
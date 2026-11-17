CC       = g++
CFLAGS   = -Wall -Wextra -O2

BIN_HASH      = proyecto_hash
BIN_LISTA     = proyecto_lista
BIN_MAP       = proyecto_map
BIN_UNORDERED = proyecto_unordered

DEPS_HASH      = main.cpp tablaHash.h articulo.h
DEPS_LISTA     = mainListaEnlazadaSimple.cpp listaEnlazadaSimple.h articulo.h
DEPS_MAP       = mainMap.cpp articulo.h
DEPS_UNORDERED = mainUMap.cpp articulo.h

all: $(BIN_HASH) $(BIN_LISTA) $(BIN_MAP) $(BIN_UNORDERED)

$(BIN_HASH): $(DEPS_HASH)
	$(CC) $(CFLAGS) main.cpp -o $(BIN_HASH)

$(BIN_LISTA): $(DEPS_LISTA)
	$(CC) $(CFLAGS) mainListaEnlazadaSimple.cpp -o $(BIN_LISTA)

$(BIN_MAP): $(DEPS_MAP)
	$(CC) $(CFLAGS) mainMap.cpp -o $(BIN_MAP)

$(BIN_UNORDERED): $(DEPS_UNORDERED)
	$(CC) $(CFLAGS) mainUMap.cpp -o $(BIN_UNORDERED)

pruebas: $(BIN_HASH) $(BIN_LISTA) $(BIN_MAP) $(BIN_UNORDERED)
	@for bin in $(BIN_HASH) $(BIN_LISTA) $(BIN_MAP) $(BIN_UNORDERED); do \
		echo "=== Probando $$bin ==="; \
		for entrada in ../datos/*.in; do \
			esperada="$${entrada%.in}.out"; \
			if [ -f "$$esperada" ]; then \
				./$$bin < "$$entrada" > /tmp/salida.txt; \
				if diff -q /tmp/salida.txt "$$esperada" > /dev/null; then \
					echo "  OK    $$(basename "$$entrada")"; \
				else \
					echo "  FALLA $$(basename "$$entrada")"; \
					diff /tmp/salida.txt "$$esperada" | head -5; \
				fi; \
			fi; \
		done; \
	done


N ?= 10

benchmark: all
	@if ! echo "$(N)" | grep -Eq '^[0-9]+$$' || [ "$(N)" -eq 0 ]; then \
		echo "Error: N debe ser un entero mayor que 0"; \
		exit 1; \
	fi
	@printf "%-25s | %-12s | %-14s | %-12s | %-12s\n" "Caso de Prueba" "Lista (ms)" "TablaHash (ms)" "Map (ms)" "Unordered (ms)"
	@printf -- "-----------------------------------------------------------------------------------------------\n"
	@for entrada in ../datos/*.in; do \
		if [ -f "$$entrada" ]; then \
			nombre=$$(basename "$$entrada"); \
			for bin in $(BIN_LISTA) $(BIN_HASH) $(BIN_MAP) $(BIN_UNORDERED); do \
				total=0; \
				for i in $$(seq 1 $(N)); do \
					inicio=$$(date +%s%N); \
					./$$bin < "$$entrada" > /dev/null; \
					fin=$$(date +%s%N); \
					tiempo=$$(( (fin-inicio)/1000000 )); \
					total=$$((total+tiempo)); \
				done; \
				promedio=$$(awk -v t=$$total -v n=$(N) 'BEGIN { printf "%.3f", t/n }'); \
				case $$bin in \
					$(BIN_LISTA)) t_lista=$$promedio ;; \
					$(BIN_HASH)) t_hash=$$promedio ;; \
					$(BIN_MAP)) t_map=$$promedio ;; \
					$(BIN_UNORDERED)) t_unordered=$$promedio ;; \
				esac; \
			done; \
			printf "%-25s | %12s | %14s | %12s | %12s\n" "$$nombre" "$$t_lista" "$$t_hash" "$$t_map" "$$t_unordered"; \
		fi; \
	done


clean:
	rm -f $(BIN_HASH) $(BIN_LISTA) $(BIN_MAP) $(BIN_UNORDERED) *.o /tmp/salida.txt

.PHONY: all pruebas benchmark clean

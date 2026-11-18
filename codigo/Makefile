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


N ?= 20
CSV = ../datos/benchmark.csv

benchmark: all
	@echo "archivo,n,lista_ms,tabla_hash_ms,map_ms,unordered_ms,repeticiones" > $(CSV)
	@for entrada in ../datos/*.in; do \
		if [ -f "$$entrada" ]; then \
			nombre=$$(basename "$$entrada"); \
			case $$nombre in \
				prueba-1.in) n=7 ;; \
				prueba-2.in) n=30 ;; \
				prueba-3.in) n=30 ;; \
				prueba-4.in) n=104 ;; \
				prueba-5.in) n=10000 ;; \
				prueba-6.in) n=50000 ;; \
				prueba-7.in) n=100000 ;; \
			esac; \
			for bin in $(BIN_LISTA) $(BIN_HASH) $(BIN_MAP) $(BIN_UNORDERED); do \
				total=0; \
				for i in $$(seq 1 $(N)); do \
					inicio=$$(date +%s%N); \
					./$$bin < "$$entrada" > /dev/null; \
					fin=$$(date +%s%N); \
					tiempo=$$((fin-inicio)); \
					total=$$((total+tiempo)); \
				done; \
				promedio=$$(awk -v t=$$total -v n=$(N) 'BEGIN { printf "%.3f", t/n/1000000 }'); \
				case $$bin in \
					$(BIN_LISTA)) t_lista=$$promedio ;; \
					$(BIN_HASH)) t_hash=$$promedio ;; \
					$(BIN_MAP)) t_map=$$promedio ;; \
					$(BIN_UNORDERED)) t_unordered=$$promedio ;; \
				esac; \
			done; \
			echo "$$nombre,$$n,$$t_lista,$$t_hash,$$t_map,$$t_unordered,$(N)" >> $(CSV); \
		fi; \
	done

clean:
	rm -f $(BIN_HASH) $(BIN_LISTA) $(BIN_MAP) $(BIN_UNORDERED) *.o /tmp/salida.txt

.PHONY: all pruebas benchmark clean

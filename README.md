# Algoritmo de Booth - Pruebas de Funcionamiento
## Descripción Breve
Este programa implementa el algoritmo de Booth para realizar multiplicaciones con números binarios en representación de complemento a 2. El sistema incluye:

- Conversión automática entre formatos decimal y binario
- Visualización paso a paso del proceso de multiplicación
- Soporte para números positivos y negativos
- Validación de resultados
  
## Casos de Prueba con Resultados Esperados

### Prueba 1: 4 bits (3 × -2)
```cpp
Entradas:
Multiplicando = 3
Multiplicador = -2
Bits = 4

Proceso:
| A     | Q     | Q-1 | M     | Operacion      | Ciclo  |
|-------|-------|-----|-------|----------------|--------|
| 0000  | 1110  |  0  | 0011  | Inicial        | 0      |
| 1101  | 1110  |  0  |       | A = A-M        | 1      |
| 1110  | 1111  |  0  |       | Shift          | 1      |
| 0001  | 1111  |  1  |       | A = A+M        | 2      |
| 0000  | 1111  |  1  |       | Shift          | 2      |
| 1111  | 1111  |  1  |       | No op          | 3      |
| 1111  | 1111  |  1  |       | Shift          | 3      |

Resultado:
Binario: 11111010
Decimal: -6
Verificación: 3 × -2 = -6 ✔


###--------------------------------------------------
Entradas:
Multiplicando = -5
Multiplicador = 3
Bits = 5

Proceso:
| A     | Q     | Q-1 | M     | Operacion      | Ciclo  |
|-------|-------|-----|-------|----------------|--------|
| 00000 | 00011 |  0  | 11011 | Inicial        | 0      |
| 00100 | 00011 |  0  |       | A = A-M        | 1      |
| 00010 | 00001 |  1  |       | Shift          | 1      |
| 11101 | 00001 |  1  |       | A = A+M        | 2      |
| 11110 | 10000 |  1  |       | Shift          | 2      |
| 11111 | 01000 |  0  |       | No op          | 3      |
| 11111 | 10100 |  0  |       | Shift          | 3      |

Resultado:
Binario: 1111110100
Decimal: -15
Verificación: -5 × 3 = -15 ✔


#--------------------------------------------------------
Entradas:
Multiplicando = 127
Multiplicador = 1
Bits = 8

Proceso:
| A     | Q     | Q-1 | M     | Operacion      | Ciclo  |
|-------|-------|-----|-------|----------------|--------|
| 00000000 | 00000001 |  0  | 01111111 | Inicial        | 0      |
| 10000001 | 00000001 |  0  |       | A = A-M        | 1      |
| 11000000 | 10000000 |  1  |       | Shift          | 1      |
| 00111111 | 10000000 |  1  |       | A = A+M        | 2      |
| 00011111 | 11000000 |  0  |       | Shift          | 2      |

Resultado:
Binario: 0001111111000000
Decimal: 127
Verificación: 127 × 1 = 127 ✔

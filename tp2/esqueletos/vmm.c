#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Campos da tabela de páginas
#define PT_FIELDS 5           // 4 campos na tabela
#define PT_FRAMEID 0          // Endereço da memória física
#define PT_MAPPED 1           // Endereço presente na tabela (dirty)
#define PT_REFERENCE_BIT 2    // Bit de referencia
#define PT_REFERENCE_MODE 3   // Tipo de acesso, converter para char
#define PT_AGING_COUNTER 4    // Contador para aging

// Tipos de acesso
#define READ 'r'
#define WRITE 'w'

// Define a função que simula a tabela de páginas
typedef int (*eviction_f)(int8_t**, int);

typedef struct {
  char *name;
  void *function;
} paging_policy_t;

// Codifique as reposições a partir daqui!
int fifo(int8_t** page_table, int last_page) {
  return 1;
}

int second_chance(int8_t** page_table, int last_page) {
  return 1;
}

int lfu(int8_t** page_table, int last_page) {
  return 1;
}

int aging(int8_t** page_table, int last_page) {
  return 1;
}

int random_page(int8_t** page_table, int last_page) {
  return 1;
}

int find_next_frame(int *physical_memory, int *num_free_frames,
                    int num_frames, int *prev_free) {
  if (*num_free_frames == 0) {
    return -1;
  }

  // Procura por um frame livre de forma circula na memória.
  // Não é muito eficiente, mas fazer um hash em C seria mais custoso.
  while (physical_memory[*prev_free] == 1) {
    *prev_free = (*prev_free + 1) % num_frames;
  }
  return *prev_free;
}

int simulate(int8_t **page_table, int num_pages, int *prev_page,
             int *physical_memory, int *num_free_frames, int num_frames,
             int *prev_free, int *frame_to_page, int virt_addr,
             char access_type, eviction_f evict) {
  if (virt_addr >= num_pages || virt_addr < 0) {
    printf("Invalid access \n");
    exit(1);
  }

  int8_t *page_table_data = page_table[virt_addr];
  int8_t frame_addr = page_table_data[PT_FRAMEID];
  int8_t mapped = page_table_data[PT_MAPPED];
  int8_t referenced = page_table_data[PT_REFERENCE_BIT];
  char last_access_type = (char) page_table_data[PT_REFERENCE_MODE];

  int next_frame_addr;
  if (mapped == 1) {
    page_table_data[PT_REFERENCE_BIT] = 1;
    return 0; // Not Page Fault!
  }

  if (*num_free_frames > 0) { // Ainda temos memória física livre!
    int next_frame_addr = find_next_frame(physical_memory, num_free_frames,
                                          num_frames, prev_free);
    frame_to_page[next_frame_addr] = virt_addr;
    *num_free_frames = *num_free_frames - 1;
  } else { // Precisamos liberar a memória!
    next_frame_addr = evict(page_table, *prev_page);
    int prev_page = frame_to_page[next_frame_addr];
    page_table_data[PT_FRAMEID] = -1;
    page_table_data[PT_MAPPED] = 0;
    page_table_data[PT_REFERENCE_BIT] = 0;
    page_table_data[PT_REFERENCE_MODE] = 0;
  }

  // Coloca endereço físico na tabela de páginas!
  page_table_data[PT_FRAMEID] = next_frame_addr;
  page_table_data[PT_MAPPED] = 1;
  page_table_data[PT_REFERENCE_BIT] = 1;
  page_table_data[PT_REFERENCE_MODE] = (int) access_type;
  *prev_page = virt_addr;
  return 1; // Page Fault!
}

int parse(char *opt) {
  char* remainderString;
  int returnVal = strtol(opt, &remainderString, 10);
  if (strcmp(remainderString, opt) == 0) {
    printf("Error parsing: %s\n", opt);
    exit(1);
  }
  return returnVal;
}

int main(int argc, char **argv) {
  if (argc < 5) {
    printf("Usage %s <numPages> <numFrames> <algorithm> <clockFreq>", argv[0]);
    exit(1);
  }

  int num_pages = parse(argv[0]);
  int num_frames = parse(argv[1]);
  char *algorithm = argv[2];
  int clock_freq = parse(argv[3]);

  // Aponta para cada função que realmente roda a política de parse
  paging_policy_t policies[] = {
    {"fifo", *fifo},
    {"second_chance", *second_chance},
    {"lfu", *lfu},
    {"aging", *aging}
  };

  eviction_f evict = NULL;
  for (int i = 0; i < 4; i++) {
    if (strcmp(policies[i].name, algorithm) == 0) {
      evict = policies[i].function;
      break;
    }
  }

  if (evict == NULL) {
    printf("Please pass a valid paging algorithm.\n");
    exit(1);
  }

  // Aloca tabela de páginas
  int8_t **page_table = (int8_t **) malloc(num_pages * sizeof(int8_t*));
  for (int i = 0; i < num_pages; i++) {
    page_table[i] = (int8_t *) malloc(PT_FIELDS * sizeof(int8_t));
  }

  // Memória Real é apenas uma tabela de bits (na verdade uso ints) indicando
  // quais frames/molduras estão livre. 0 == livre!
  int *physical_memory = (int *) malloc(num_frames * sizeof(int));
  int *frame_to_page = (int *) malloc(num_frames * sizeof(int));
  for (int i = 0; i < num_frames; i++) {
    physical_memory[i] = 0;
    frame_to_page[i] = -1;
  }
  int next_free = 0;

  // Liberando os mallocs
  for (int i = 0; i < num_pages; i++) {
    free(page_table[i]);
  }
  free(page_table);
  free(physical_memory);
}

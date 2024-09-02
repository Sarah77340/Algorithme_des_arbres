CODEDIR = .

VISITE = $(CODEDIR)/visites_uniques
ENSEMBLE = $(CODEDIR)/ensemble
VARIANTS = tab_non_trie lst tab_trie
TARGETS = $(addprefix $(VISITE)_, $(VARIANTS))

all: tab_non_trie lst tab_trie

lst: visites_uniques_lst
tab_trie: visites_uniques_tab_trie
tab_non_trie: visites_uniques_tab_non_trie

$(VISITE)_%: $(ENSEMBLE)_%.o $(VISITE).o
	$(CC) $(LDFLAGS) $^ -o $@

$(VISITE).o: $(VISITE).c $(ENSEMBLE).h
$(ENSEMBLE)_%.o: $(ENSEMBLE)_%.c $(ENSEMBLE).h

.PHONY: clean

clean:
	$(RM) *.o $(TARGETS)

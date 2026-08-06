DOXYGEN := doxygen
DOCS_OUTPUT := build/docs/doxygen

.PHONY: help docs docs-clean

help:
	@echo "Kullanılabilir komutlar:"
	@echo "  make docs        Doxygen belgelerini oluşturur"
	@echo "  make docs-clean  Oluşturulan belgeleri siler"

docs:
	@command -v $(DOXYGEN) >/dev/null || { \
		echo "Hata: Doxygen bulunamadı."; \
		echo "Kurulum: brew install doxygen graphviz"; \
		exit 1; \
	}
	@mkdir -p $(DOCS_OUTPUT)
	$(DOXYGEN) Doxyfile
	@echo "Belgeler oluşturuldu: $(DOCS_OUTPUT)/html/index.html"

docs-clean:
	$(RM) -r $(DOCS_OUTPUT)

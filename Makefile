OUTPUTDIR = ./bin/

format:
	clang-format -i -style=WebKit src/*.cpp $(CXXSOURCES)

clean:
	$(RM) -rf $(OUTPUTDIR)
	$(RM) ./*.gc??
	$(RM) ./*.o
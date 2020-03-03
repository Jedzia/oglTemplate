if(NOT EXISTS ${PANDOC_EXECUTABLE})
    # find_program(PANDOC_EXECUTABLE NAMES pandoc)
    find_program(PANDOC_EXECUTABLE pandoc)
    mark_as_advanced(PANDOC_EXECUTABLE)
    if(NOT EXISTS ${PANDOC_EXECUTABLE})
        message(WARNING "Pandoc not found. Install Pandoc (http://johnmacfarlane.net/pandoc/) or set cache variable PANDOC_EXECUTABLE. No Documentation is built.")
        return()
    endif()
endif()


INCLUDE(pandocology)

add_document(
        TARGET              pdf
#        PANDOC_DIRECTIVES   -f asciidoc
        OUTPUT_FILE         TheDatabaseThingsBook.pdf
        SOURCES             TheDatabaseThingsBook.md
)
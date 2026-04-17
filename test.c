#include "test.h"

int main(int argc, char *argv[])
{
    int order = 0, maxNumEdges = 0, embedFlags = 0, embedResult = 0, embedIntegrityCheckResult = 0;
    graphP graphToEmbed = NULL, graphToCheckEmbeddingIntegrity = NULL;

    if (argc != 2)
    {
        printf("No graph input filename provided.\n");
        return -1;
    }

    graphToEmbed = gp_New();
    if (graphToEmbed == NULL)
    {
        printf("Unable to allocate graph to embed.\n");
        return -1;
    }

    graphToCheckEmbeddingIntegrity = gp_New();
    if (graphToCheckEmbeddingIntegrity == NULL)
    {
        printf("Unable to allocate graph to check embed result integrity.\n");

        gp_Free(&graphToEmbed);

        return -1;
    }

    if (gp_Read(graphToEmbed, argv[1]) != OK)
    {
        printf("Unable to read %s into graphP\n", argv[1]);

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    order = gp_GetN(graphToEmbed);

    if (gp_InitGraph(graphToCheckEmbeddingIntegrity, order) != OK)
    {
        printf("Unable to initialize graph to check embed result integrity.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    maxNumEdges = (order * (order - 1)) / 2;
    if (gp_EnsureEdgeCapacity(graphToEmbed, maxNumEdges) != OK)
    {
        printf("Failed to Ensure Edge Capacity of graph.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    if (gp_CopyGraph(graphToCheckEmbeddingIntegrity, graphToEmbed) != OK)
    {
        printf("Failed to make a copy of the graph for embedding integrity check.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    if (gp_ExtendWith_K33Search(graphToEmbed) != OK)
    {
        printf("Failed to extend graph to embed with structures necessary for K_{3,3} homeomorph search.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    embedFlags = EMBEDFLAGS_SEARCHFORK33;
    embedResult = gp_Embed(graphToEmbed, embedFlags);
    if (embedResult != OK && embedResult != NONEMBEDDABLE)
    {
        printf("Failed to run K_{3,3} homeomorph search.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    embedIntegrityCheckResult = gp_TestEmbedResultIntegrity(graphToEmbed, graphToCheckEmbeddingIntegrity, embedResult);
    if (embedIntegrityCheckResult != OK && embedIntegrityCheckResult != NONEMBEDDABLE)
    {
        printf("Embed result integrity check for K_{3,3} homeomorph search failed.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    if (gp_Write(graphToEmbed, "test_output.txt", WRITE_ADJLIST) != OK)
    {
        printf("Failed to write graph.\n");

        gp_Free(&graphToEmbed);
        gp_Free(&graphToCheckEmbeddingIntegrity);

        return -1;
    }

    gp_Free(&graphToEmbed);
    gp_Free(&graphToCheckEmbeddingIntegrity);

    return 0;
}
#include "Set.h"
#include "GraphMat.h"
#include "GraphList.h"
#include "W_Or_Graphs.h"

int main()
{
    WGraphList G;

    G.AdV();
    G.AdV();
    G.AdV();

    G.ShowList();

    G.AdE(1, 2, 7);
    G.AdE(2, 3, 5);
    G.AdE(1, 3, 5);

    G.ShowList();

    G.DelV(2);

    G.ShowList();
    G.AdV();
    G.AdE(4, 3, 5);
    G.ShowList();

	return 0;
}
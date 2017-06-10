/**CFile****************************************************************

  FileName    [wlcShow.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Verilog parser.]

  Synopsis    [Parses several flavors of word-level Verilog.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - August 22, 2014.]

  Revision    [$Id: wlcShow.c,v 1.00 2014/09/12 00:00:00 alanmi Exp $]

***********************************************************************/

#include "wlc.h"

ABC_NAMESPACE_IMPL_START

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////


/**Function*************************************************************

  Synopsis    [Writes the graph structure of WLC for DOT.]

  Description [Useful for graph visualization using tools such as GraphViz: 
  http://www.graphviz.org/]
  
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Wlc_NtkDumpDot( Wlc_Ntk_t * p, char * pFileName, Vec_Int_t * vBold )
{
    FILE * pFile;
    Wlc_Obj_t * pNode;
    int LevelMax, Prev, Level, i;

    if ( Wlc_NtkObjNum(p) > 2000 )
    {
        fprintf( stdout, "Cannot visualize WLC with more than %d nodes.\n", 2000 );
        return;
    }
    if ( (pFile = fopen( pFileName, "w" )) == NULL )
    {
        fprintf( stdout, "Cannot open the intermediate file \"%s\".\n", pFileName );
        return;
    }

    // mark the nodes
    if ( vBold )
        Wlc_NtkForEachObjVec( vBold, p, pNode, i )
            pNode->Mark = 1;

    // compute levels
    LevelMax = 1 + Wlc_NtkCreateLevelsRev( p );

    // write the DOT header
    fprintf( pFile, "# %s\n",  "WLC structure generated by ABC" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "digraph WLC {\n" );
    fprintf( pFile, "size = \"7.5,10\";\n" );
//  fprintf( pFile, "ranksep = 0.5;\n" );
//  fprintf( pFile, "nodesep = 0.5;\n" );
    fprintf( pFile, "center = true;\n" );
//  fprintf( pFile, "orientation = landscape;\n" );
//  fprintf( pFile, "edge [fontsize = 10];\n" );
//  fprintf( pFile, "edge [dir = none];\n" );
    fprintf( pFile, "edge [dir = back];\n" );
    fprintf( pFile, "\n" );

    // labels on the left of the picture
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  node [shape = plaintext];\n" );
    fprintf( pFile, "  edge [style = invis];\n" );
    fprintf( pFile, "  LevelTitle1 [label=\"\"];\n" );
    fprintf( pFile, "  LevelTitle2 [label=\"\"];\n" );
    // generate node names with labels
    for ( Level = LevelMax; Level >= 0; Level-- )
    {
        // the visible node name
        fprintf( pFile, "  Level%d", Level );
        fprintf( pFile, " [label = " );
        // label name
        fprintf( pFile, "\"" );
        fprintf( pFile, "\"" );
        fprintf( pFile, "];\n" );
    }

    // genetate the sequence of visible/invisible nodes to mark levels
    fprintf( pFile, "  LevelTitle1 ->  LevelTitle2 ->" );
    for ( Level = LevelMax; Level >= 0; Level-- )
    {
        // the visible node name
        fprintf( pFile, "  Level%d",  Level );
        // the connector
        if ( Level != 0 )
            fprintf( pFile, " ->" );
        else
            fprintf( pFile, ";" );
    }
    fprintf( pFile, "\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate title box on top
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    fprintf( pFile, "  LevelTitle1;\n" );
    fprintf( pFile, "  title1 [shape=plaintext,\n" );
    fprintf( pFile, "          fontsize=20,\n" );
    fprintf( pFile, "          fontname = \"Times-Roman\",\n" );
    fprintf( pFile, "          label=\"" );
    fprintf( pFile, "%s", "WLC structure generated by ABC" );
    fprintf( pFile, "\\n" );
    fprintf( pFile, "Benchmark \\\"%s\\\". ", p->pName );
//    fprintf( pFile, "Time was %s. ",  Extra_TimeStamp() );
    fprintf( pFile, "\"\n" );
    fprintf( pFile, "         ];\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate statistics box
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    fprintf( pFile, "  LevelTitle2;\n" );
    fprintf( pFile, "  title2 [shape=plaintext,\n" );
    fprintf( pFile, "          fontsize=18,\n" );
    fprintf( pFile, "          fontname = \"Times-Roman\",\n" );
    fprintf( pFile, "          label=\"" );
    fprintf( pFile, "The word-level network contains %d nodes and spans %d levels.", Wlc_NtkObjNum(p)-Wlc_NtkCiNum(p), LevelMax-1 );
    fprintf( pFile, "\\n" );
    fprintf( pFile, "\"\n" );
    fprintf( pFile, "         ];\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate the COs
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    // the labeling node of this level
    fprintf( pFile, "  Level%d;\n",  LevelMax );
    // generate the CO nodes
    Wlc_NtkForEachCo( p, pNode, i )
    {
        pNode = Wlc_ObjCo2PoFo(p, i);
        fprintf( pFile, "  NodePo%d [label = \"%s_in %d\"", Wlc_ObjId(p, pNode), Wlc_ObjName(p, Wlc_ObjId(p, pNode)), Wlc_ObjRange(pNode) ); 
        fprintf( pFile, ", shape = %s", i < Wlc_NtkPoNum(p) ? "invtriangle" : "box" );
        fprintf( pFile, ", color = coral, fillcolor = coral" );
        fprintf( pFile, "];\n" );
    }
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate nodes of each rank
    for ( Level = LevelMax - 1; Level > 0; Level-- )
    {
        fprintf( pFile, "{\n" );
        fprintf( pFile, "  rank = same;\n" );
        // the labeling node of this level
        fprintf( pFile, "  Level%d;\n",  Level );
        Wlc_NtkForEachObj( p, pNode, i )
        {
            if ( (int)Wlc_ObjLevel(p, pNode) != Level )
                continue;

            if ( pNode->Type == WLC_OBJ_CONST )
            {
                fprintf( pFile, "  Node%d [label = \"0x", i ); 
                Abc_TtPrintHexArrayRev( pFile, (word *)Wlc_ObjConstValue(pNode), (Wlc_ObjRange(pNode) + 3) / 4 );
                fprintf( pFile, "\"" ); 
            }
            else if ( pNode->Type == WLC_OBJ_BUF || pNode->Type == WLC_OBJ_MUX )
                fprintf( pFile, "  Node%d [label = \"%d\"", i, Wlc_ObjRange(pNode) ); 
            else if ( pNode->Type >= WLC_OBJ_LOGIC_NOT && pNode->Type <= WLC_OBJ_COMP_MOREEQU )
                fprintf( pFile, "  Node%d [label = \"%s\"", i, Wlc_ObjTypeName(pNode) ); 
            else
                fprintf( pFile, "  Node%d [label = \"%s %d\"", i, Wlc_ObjTypeName(pNode), Wlc_ObjRange(pNode) ); 

            if ( pNode->Type == WLC_OBJ_ARI_MULTI )
                fprintf( pFile, ", shape = doublecircle" );
            else if ( pNode->Type >= WLC_OBJ_COMP_EQU && pNode->Type <= WLC_OBJ_COMP_MOREEQU )
                fprintf( pFile, ", shape = diamond" );
            else if ( pNode->Type == WLC_OBJ_BIT_SELECT || pNode->Type == WLC_OBJ_BIT_CONCAT )
                fprintf( pFile, ", shape = box" );
            else if ( pNode->Type == WLC_OBJ_BUF || pNode->Type == WLC_OBJ_BIT_ZEROPAD || pNode->Type == WLC_OBJ_BIT_SIGNEXT )
                fprintf( pFile, ", shape = triangle" );
            else if ( pNode->Type == WLC_OBJ_MUX )
                fprintf( pFile, ", shape = trapezium" );
            else
                fprintf( pFile, ", shape = ellipse" );

            if ( vBold ? pNode->Mark : ((pNode->Type >= WLC_OBJ_ARI_ADD && pNode->Type <= WLC_OBJ_ARI_SQUARE) || pNode->Type == WLC_OBJ_BIT_NOT) )
                fprintf( pFile, ", style = filled" );
            fprintf( pFile, "];\n" );
        }
        fprintf( pFile, "}" );
        fprintf( pFile, "\n" );
        fprintf( pFile, "\n" );
    }

    // generate the CI nodes
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    // the labeling node of this level
    fprintf( pFile, "  Level%d;\n",  0 );
    // generate the CI nodes
    Wlc_NtkForEachCi( p, pNode, i )
    {
        fprintf( pFile, "  Node%d [label = \"%s %d\"", Wlc_ObjId(p, pNode), Wlc_ObjName(p, Wlc_ObjId(p, pNode)), Wlc_ObjRange(pNode) ); 
        fprintf( pFile, ", shape = %s", i < Wlc_NtkPiNum(p) ? "triangle" : "box" );
        fprintf( pFile, ", color = coral, fillcolor = coral" );
        fprintf( pFile, "];\n" );
    }
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate invisible edges from the square down
    fprintf( pFile, "title1 -> title2 [style = invis];\n" );
    Wlc_NtkForEachCo( p, pNode, i )
    {
        pNode = Wlc_ObjCo2PoFo( p, i );
        fprintf( pFile, "title2 -> NodePo%d [style = invis];\n", Wlc_ObjId(p, pNode) );
    }
    // generate invisible edges among the COs
    Prev = -1;
    Wlc_NtkForEachCo( p, pNode, i )
    {
        pNode = Wlc_ObjCo2PoFo( p, i );
        if ( i > 0 )
            fprintf( pFile, "NodePo%d -> NodePo%d [style = invis];\n", Prev, Wlc_ObjId(p, pNode) );
        Prev = Wlc_ObjId(p, pNode);
    }
    // generate invisible edges among the CIs
    Prev = -1;
    Wlc_NtkForEachCi( p, pNode, i )
    {
        if ( i > 0 )
            fprintf( pFile, "Node%d -> Node%d [style = invis];\n", Prev, Wlc_ObjId(p, pNode) );
        Prev = Wlc_ObjId(p, pNode);
    }

    // generate edges
    Wlc_NtkForEachCo( p, pNode, i )
    {
        fprintf( pFile, "NodePo%d",  Wlc_ObjId(p, Wlc_ObjCo2PoFo(p, i)) );
        fprintf( pFile, " -> " );
        fprintf( pFile, "Node%d",  Wlc_ObjId(p, pNode) );
        fprintf( pFile, " [" );
        fprintf( pFile, "style = %s", pNode->Signed? "dotted" : "solid" );
        fprintf( pFile, "]" );
        fprintf( pFile, ";\n" );
    }
    Wlc_NtkForEachObj( p, pNode, i )
    {
        int k, iFanin;
        if ( Wlc_ObjIsCi(pNode) )
            continue;
        // generate the edge from this node to the next
        Wlc_ObjForEachFanin( pNode, iFanin, k )
        {
            fprintf( pFile, "Node%d",  i );
            fprintf( pFile, " -> " );
            fprintf( pFile, "Node%d",  iFanin );
            fprintf( pFile, " [" );
            fprintf( pFile, "style = %s", Wlc_NtkObj(p, iFanin)->Signed? "dotted" : "solid" );
            if ( pNode->Type == WLC_OBJ_MUX && k == 0 )
                fprintf( pFile, ", style = %s", "bold" );
            fprintf( pFile, "]" );
            fprintf( pFile, ";\n" );
        }
    }
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );
    fclose( pFile );

    // unmark nodes
    if ( vBold )
        Wlc_NtkCleanMarks( p );
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Wlc_NtkShow( Wlc_Ntk_t * p, Vec_Int_t * vBold )
{
    extern void Abc_ShowFile( char * FileNameDot );
    FILE * pFile;
    char FileNameDot[200];
    sprintf( FileNameDot, "%s", Extra_FileNameGenericAppend(p->pName, ".dot") );
    // check that the file can be opened
    if ( (pFile = fopen( FileNameDot, "w" )) == NULL )
    {
        fprintf( stdout, "Cannot open the intermediate file \"%s\".\n", FileNameDot );
        return;
    }
    fclose( pFile );
    // generate the file
    Wlc_NtkDumpDot( p, FileNameDot, vBold );
    // visualize the file 
    Abc_ShowFile( FileNameDot );
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


ABC_NAMESPACE_IMPL_END


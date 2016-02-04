#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

struct vertex{
    double coord_x;
    double coord_y;
};
typedef struct vertex vtx;

vtx* initialize_vertex(vtx* B)
{
    B = (vtx*)malloc(sizeof(vtx));
    B->coord_x = 0;
    B->coord_y = 0;
    //show_vertex(B);
    return B;
}

void show_vertex(vtx *B)
{
    printf("%lf,%lf & ",B->coord_x,B->coord_y);
}

void start_BGW(vtx* B,vtx* G,vtx* W)
{
    B->coord_x = 0;
    B->coord_y = 0;

    G->coord_x = 1.2;
    G->coord_y = 0;

    W->coord_x = 0;
    W->coord_y = 0.8;
    printf("Start with the three vertices:\n");
    show_vertex(B);
    show_vertex(G);
    show_vertex(W);
}

double f(vtx * B)
{
    double x = B->coord_x;
    double y = B->coord_y;
    return pow(x,2) - 4 * x + pow(y,2) - y - x * y;
}

void midof(vtx* M, vtx* B, vtx* G)
{
    M->coord_x = (B->coord_x + G->coord_x) / 2;
    M->coord_y = (B->coord_y + G->coord_y) / 2;
    //printf("\nM = \n");
    //show_vertex(M);
}

void expansion(vtx* R, vtx* M, vtx* W)
{
    R->coord_x = 2 * M->coord_x - W->coord_x;
    R->coord_y = 2 * M->coord_y - W->coord_y;
    //printf("\nR = \n");
    //show_vertex(R);
}

void compute_E(vtx* E, vtx* R, vtx* M)
{
    E->coord_x = 2 * R->coord_x - M->coord_x;
    E->coord_y = 2 * R->coord_y - M->coord_y;
}

void situation_1(vtx* B, vtx* R, vtx* W,vtx* M)
{
    vtx* E;
    E = initialize_vertex(E);
    if(f(B) < f(R)){
        replace(W,R);
    }
    else{
        compute_E(E, R, M);
        if(f(E) < f(B)){
            replace(W,E);
        }
        else{
            replace(W,R);
        }
    }
    return;
}

void situation_2(vtx*B, vtx* R, vtx* W, vtx* M, vtx* G)
{
    if(f(R) < f(W)){
        replace(W,R);
    }

    midof(M,B,G);
    expansion(R,M,W);
    vtx *C, *C2, *S;
    C = initialize_vertex(C);
    C2 = initialize_vertex(C2);
    S = initialize_vertex(S);

    compute_C(C,W,M);
    compute_C2(C2,M,R);

    if(f(C) > f(C2)){
        replace(C,C2);
    }

    if(f(C) < f(M)){
        replace(W,C);
    }
    else{
        compute_S(S,B,W);
        replace(W,S);
        replace(G,M);
    }
}

void compute_S(vtx* S, vtx* B, vtx* W)
{
    S->coord_x = (W->coord_x + B->coord_x) / 2;
    S->coord_y = (W->coord_y + B->coord_y) / 2;
}

void compute_C(vtx* C,vtx* W,vtx* M)
{
    C->coord_x = (W->coord_x + M->coord_x) / (double)2;
    C->coord_y = (W->coord_y + M->coord_y) / (double)2;
    return;
}

void compute_C2(vtx* C2,vtx* M,vtx* R)
{
    C2->coord_x = (R->coord_x + M->coord_x) / 2;
    C2->coord_y = (R->coord_y + M->coord_y) / 2;
}

void replace(vtx* A, vtx* B)
{
    A->coord_x = B->coord_x;
    A->coord_y = B->coord_y;
}

void show_triangle(vtx* B, vtx* G, vtx* W)
{
    //printf("\nbest point\t\tGood point\t\tWorst point\n");
    show_vertex(B);
    show_vertex(G);
    show_vertex(W);
    printf("\n");
}

void sort(vtx* B,vtx* G,vtx* W)
{
    vtx *temp;
    temp = initialize_vertex(temp);

    if(f(G) < f(B)){
        //printf("B<->G\n");
        replace(temp,B);
        replace(B,G);
        replace(G,temp);
    }
    //printf("best & good:");
    //show_triangle(B,G,W);


    if(f(W) < f(B)){
        //printf("B<->W\n");
        replace(temp,B);
        replace(B,W);
        replace(W,temp);
        //show_triangle(B,G,W);

        replace(temp,W);
        replace(W,G);
        replace(G,temp);
        //show_triangle(B,G,W);
        return;
    }
    if(f(G) < f(W)){
        return;
    }
    if(f(W) < f(G) && f(W) > f(B)){
        replace(temp,G);
        replace(G,W);
        replace(W,temp);
        return;
    }
}
#endif // OPERATION_H_INCLUDED

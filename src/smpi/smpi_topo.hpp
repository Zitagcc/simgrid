/* Copyright (c) 2010-2017. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef SMPI_TOPO_HPP_INCLUDED
#define SMPI_TOPO_HPP_INCLUDED

#include "src/smpi/smpi_comm.hpp"
#include "src/smpi/smpi_status.hpp"

typedef enum MPIR_Topo_type {
  MPI_GRAPH=1,
  MPI_CART=2,
  MPI_DIST_GRAPH=3,
  MPI_INVALID_TOPO=-1
} MPIR_Topo_type;

typedef SMPI_Topology *MPI_Topology;

namespace simgrid{
namespace smpi{

class Topo {
  public:
    virtual ~Topo()=default;
  protected:
  MPI_Comm comm_;
};


class Topo_Cart: public Topo {
  private:
    int nnodes_ = 0;
    int ndims_;
    int *dims_;
    int *periodic_;
    int *position_;
  public:
    explicit Topo_Cart(int ndims);
    ~Topo_Cart();
    Topo_Cart(MPI_Comm comm_old, int ndims, int dims[], int periods[], int reorder, MPI_Comm *comm_cart);
    Topo_Cart* sub(const int remain_dims[], MPI_Comm *newcomm) ;
    int coords(int rank, int maxdims, int coords[]) ;
    int get(int maxdims, int* dims, int* periods, int* coords);
    int rank(int* coords, int* rank);
    int shift(int direction, int disp, int *rank_source, int *rank_dest) ;
    int dim_get(int *ndims);
    static int Dims_create(int nnodes, int ndims, int dims[]);
};


class Topo_Graph: public Topo {
  private:
    int nnodes_;
    int nedges_;
    int *index_;
    int *edges_;
  public:
    Topo_Graph();
    ~Topo_Graph();
};

class Topo_Dist_Graph: public Topo {
  private:
    int indegree_;
    int *in_;
    int *in_weights_;
    int outdegree_;
    int *out_;
    int *out_weights_;
    int is_weighted_;
  public:
    Topo_Dist_Graph();
    ~Topo_Dist_Graph();
};

}
}


#endif

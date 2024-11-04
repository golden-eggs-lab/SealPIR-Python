#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "seal/seal.h"
#include <fstream>

#include <memory>
#include <vector>
#include "pir.hpp"
#include "pir_client.hpp"
#include "pir_server.hpp"

using namespace seal;
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<std::int64_t>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<Ciphertext>>); // PirQuery
PYBIND11_MAKE_OPAQUE(std::vector<Ciphertext>);              // PirReply
PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);

PYBIND11_MODULE(sealp, m)
{
    m.doc() = "Microsoft SEAL-PIR for Python";
    m.attr("__version__")  = "1.0.0";

    py::bind_vector<std::vector<double>>(m, "VectorDouble", py::buffer_protocol());
    py::bind_vector<std::vector<std::int64_t>>(m, "VectorInt", py::buffer_protocol());

    // pir.hpp
    py::class_<std::vector<std::vector<Ciphertext>>>(m, "PirQuery")
        .def(py::init());

    // pir.hpp
    py::class_<std::vector<Ciphertext>>(m, "PirReply")
        .def(py::init());

    // pir.hpp
    py::class_<StringStreamR>(m, "StringStreamR")
        .def(py::init())
        .def_readwrite("str_return", &StringStreamR::str_return)
        .def(py::pickle(
            [](const StringStreamR &s) {
                return py::make_tuple(py::bytes(s.str_return));
            },
            [](py::tuple t) {
                return StringStreamR{t[0].cast<std::string>()};
            }
            ));

    // pir.hpp
    py::class_<PirParams>(m, "PirParams")
        .def(py::init())
        .def_readwrite("enable_symmetric", &PirParams::enable_symmetric)
        .def_readwrite("enable_batching", &PirParams::enable_batching)
        .def_readwrite("enable_mswitching", &PirParams::enable_mswitching)
        .def_readwrite("ele_num", &PirParams::ele_num)
        .def_readwrite("ele_size", &PirParams::ele_size)
        .def_readwrite("elements_per_plaintext", &PirParams::elements_per_plaintext)
        .def_readwrite("num_of_plaintexts", &PirParams::num_of_plaintexts)
        .def_readwrite("d", &PirParams::d)
        .def_readwrite("expansion_ratio", &PirParams::expansion_ratio)
        .def_readwrite("nvec", &PirParams::nvec)
        .def_readwrite("slot_count", &PirParams::slot_count)
        .def(py::pickle(
            [](const PirParams &p) {
                return py::make_tuple(p.enable_symmetric, p.enable_batching, p.enable_mswitching, 
                    p.ele_num, p.ele_size, p.elements_per_plaintext, p.num_of_plaintexts, p.d, 
                    p.expansion_ratio, p.nvec, p.slot_count);
            },
            [](py::tuple t) {
                return PirParams{t[0].cast<bool>(), t[1].cast<bool>(), t[2].cast<bool>(), t[3].cast<std::uint64_t>(),
                t[4].cast<std::uint64_t>(), t[5].cast<std::uint64_t>(), t[6].cast<std::uint64_t>(), t[7].cast<std::uint32_t>(), t[8].cast<std::uint32_t>(),
                t[9].cast<std::vector<std::uint64_t>>(), t[10].cast<std::uint32_t>()};
            }
            ));

    // pir_client.hpp
    py::class_<PIRClient>(m, "PIRClient")
        .def(py::init<EncryptionParameters, PirParams>())
        .def("generate_serialized_query", &PIRClient::generate_serialized_query)
        .def("generate_query", &PIRClient::generate_query)
        .def("deserialize_reply", &PIRClient::deserialize_reply)
        .def("decode_reply", py::overload_cast<PirReply &>(&PIRClient::decode_reply), "one input arg")
        .def("decode_reply", py::overload_cast<PirReply &, std::uint64_t>(&PIRClient::decode_reply), "two input args")
        .def("extract_coeffs", py::overload_cast<Plaintext>(&PIRClient::extract_coeffs), "input one arg")
        .def("extract_coeffs", py::overload_cast<Plaintext, std::uint64_t>(&PIRClient::extract_coeffs), "input two args")
        .def("extract_bytes", &PIRClient::extract_bytes)
        .def("decrypt", &PIRClient::decrypt)
        .def("generate_galois_keys", &PIRClient::generate_galois_keys)
        .def("get_fv_index", &PIRClient::get_fv_index)
        .def("get_fv_offset", &PIRClient::get_fv_offset)
        .def("get_one", &PIRClient::get_one)
        .def("replace_element", &PIRClient::replace_element);

    // pir.hpp
    m.def("gen_encryption_params", &gen_encryption_params);

    // pir.hpp
    m.def("gen_pir_params", &gen_pir_params);

    // pir.hpp
    m.def("verify_encryption_params", &verify_encryption_params);

    // pir.hpp
    m.def("print_seal_params", &print_seal_params);

    // pir.hpp
    m.def("print_pir_params", &print_pir_params);

    // pir.hpp
    m.def("serialize_galoiskeys", &serialize_galoiskeys);

    // pir.hpp
    m.def("deserialize_galoiskeys", &deserialize_galoiskeys);

    // pir_server.hpp
    py::class_<PIRServer>(m, "PIRServer")
        .def(py::init<EncryptionParameters, PirParams>())
        .def("preprocess_database", &PIRServer::preprocess_database)
        .def("wrap_database", &PIRServer::wrap_database)
        .def("expand_query", &PIRServer::expand_query)
        .def("deserialize_query", &PIRServer::deserialize_query)
        .def("generate_reply", &PIRServer::generate_reply)
        .def("serialize_reply", &PIRServer::serialize_reply)
        .def("set_galois_key", &PIRServer::set_galois_key)
        .def("simple_set", &PIRServer::simple_set)
        .def("set_one_ct", &PIRServer::set_one_ct);
}




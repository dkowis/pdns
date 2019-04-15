#pragma once
#include "iputils.hh"

struct DOHFrontend
{
  std::string d_certFile;
  std::string d_keyFile;
  ComboAddress d_local;

  uint32_t d_idleTimeout{30};             // HTTP idle timeout in seconds
  std::vector<std::string> d_urls;
  std::string d_errortext;
  std::atomic<uint64_t> d_httpconnects;   // number of TCP/IP connections established
  std::atomic<uint64_t> d_http1queries;   // valid DNS queries received via HTTP1
  std::atomic<uint64_t> d_http2queries;   // valid DNS queries received via HTTP2
  std::atomic<uint64_t> d_tls10queries;   // valid DNS queries received via TLSv1.0
  std::atomic<uint64_t> d_tls11queries;   // valid DNS queries received via TLSv1.1
  std::atomic<uint64_t> d_tls12queries;   // valid DNS queries received via TLSv1.2
  std::atomic<uint64_t> d_tls13queries;   // valid DNS queries received via TLSv1.3
  std::atomic<uint64_t> d_tlsUnknownqueries;   // valid DNS queries received via unknown TLS version

  std::atomic<uint64_t> d_getqueries;     // valid DNS queries received via GET
  std::atomic<uint64_t> d_postqueries;    // valid DNS queries received via POST
  std::atomic<uint64_t> d_badrequests;     // request could not be converted to dns query
  std::atomic<uint64_t> d_errorresponses; // dnsdist set 'error' on response
  std::atomic<uint64_t> d_validresponses; // valid responses sent out

#ifndef HAVE_DNS_OVER_HTTPS
  void setup()
  {
  }
#else
  void setup();
#endif /* HAVE_DNS_OVER_HTTPS */
};

#ifndef HAVE_DNS_OVER_HTTPS
struct DOHUnit
{
};

#else /* HAVE_DNS_OVER_HTTPS */
struct st_h2o_req_t;

struct DOHUnit
{
  std::string query;
  ComboAddress remote;
  ComboAddress dest;
  st_h2o_req_t* req{nullptr};
  DOHUnit** self{nullptr};
  int rsock;
  uint16_t qtype;
  bool error{false};
  bool ednsAdded{false};
};

#endif /* HAVE_DNS_OVER_HTTPS  */

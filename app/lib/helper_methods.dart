import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'dart:async';

class HelperMethods {
  static const String url = "https://can.server.mylassi.xyz/";

  static Future<http.Response> post(String path, BuildContext context,
      [Object body, skipTokenRefresh = false]) async {
    var g = http.post("$url/$path", body: JSON.encode(body), headers: {
    });
    http.Response res;
    await g.then((x) => res = x);
    return res;
  }

  static Future<http.Response> get(String path, BuildContext context) async {
    var g = http.get("$url/$path", headers: {
    });
    http.Response res;
    await g.then((x) => res = x);
    return res;
  }

  static Future<http.Response> put(String path, BuildContext context,
      [Object body, bool skipTokenRefresh = false]) async {
    var g = http.put("$url/$path", body: JSON.encode(body), headers: {
    });
    http.Response res;
    await g.then((x) => res = x);
    return res;
  }

  static Future<http.Response> delete(String path, BuildContext context) async {
    var g = http.delete("$url/$path", headers: {
    });
    http.Response res;
    await g.then((x) => res = x);
    return res;
  }

  void onDataLoaded(String responseText) {
    var jsonString = responseText;
    print(jsonString);
  }
}

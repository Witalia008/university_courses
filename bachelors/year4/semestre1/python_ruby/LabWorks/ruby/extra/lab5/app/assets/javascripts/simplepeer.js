!function (e) {
    if ("object" == typeof exports && "undefined" != typeof module)module.exports = e(); else if ("function" == typeof define && define.amd)define([], e); else {
        var t;
        "undefined" != typeof window ? t = window : "undefined" != typeof global ? t = global : "undefined" != typeof self && (t = self), t.SimplePeer = e()
    }
}(function () {
    return function e(t, n, r) {
        function i(s, a) {
            if (!n[s]) {
                if (!t[s]) {
                    var u = "function" == typeof require && require;
                    if (!a && u)return u(s, !0);
                    if (o)return o(s, !0);
                    var c = new Error("Cannot find module '" + s + "'");
                    throw c.code = "MODULE_NOT_FOUND", c
                }
                var h = n[s] = {exports: {}};
                t[s][0].call(h.exports, function (e) {
                    var n = t[s][1][e];
                    return i(n ? n : e)
                }, h, h.exports, e, t, n, r)
            }
            return n[s].exports
        }

        for (var o = "function" == typeof require && require, s = 0; s < r.length; s++)i(r[s]);
        return i
    }({
        "./": [function (e, t) {
            function n(e) {
                return this instanceof n ? (o.call(this), e = s({
                    initiator: !1,
                    stream: !1,
                    config: n.config,
                    constraints: n.constraints,
                    channelName: e && e.initiator ? "simple-peer-" + a(160) : null,
                    trickle: !0
                }, e), s(this, e), i("new peer initiator: %s channelName: %s", this.initiator, this.channelName), this.destroyed = !1, this.ready = !1, this._pcReady = !1, this._channelReady = !1, this._dataStreams = [], this._iceComplete = !1, this._pc = new d(this.config, this.constraints), this._pc.oniceconnectionstatechange = this._onIceConnectionStateChange.bind(this), this._pc.onsignalingstatechange = this._onSignalingStateChange.bind(this), this._pc.onicecandidate = this._onIceCandidate.bind(this), this._channel = null, this.stream && this._setupVideo(this.stream), void(this.initiator ? (this._setupData({channel: this._pc.createDataChannel(this.channelName)}), this._pc.onnegotiationneeded = h(function () {
                    this._pc.createOffer(function (e) {
                        this._pc.setLocalDescription(e);
                        var t = function () {
                            this.emit("signal", this._pc.localDescription || e)
                        }.bind(this);
                        this.trickle || this._iceComplete ? t() : this.once("_iceComplete", t)
                    }.bind(this), this._onError.bind(this))
                }.bind(this)), window.mozRTCPeerConnection && setTimeout(this._pc.onnegotiationneeded.bind(this._pc), 0)) : this._pc.ondatachannel = this._setupData.bind(this))) : new n(e)
            }

            function r(e) {
                f.Duplex.call(this, e), this._peer = e._peer, i("new stream")
            }

            t.exports = n;
            var i = e("debug")("simple-peer"), o = e("events").EventEmitter, s = e("extend.js"), a = e("hat"), u = e("inherits"), c = e("is-typedarray"), h = e("once"), f = e("stream"), l = e("typedarray-to-buffer"), d = "undefined" != typeof window && (window.mozRTCPeerConnection || window.RTCPeerConnection || window.webkitRTCPeerConnection), p = "undefined" != typeof window && (window.mozRTCSessionDescription || window.RTCSessionDescription || window.webkitRTCSessionDescription), g = "undefined" != typeof window && (window.mozRTCIceCandidate || window.RTCIceCandidate || window.webkitRTCIceCandidate);
            u(n, o), n.config = {iceServers: [{url: "stun:23.21.150.121"}]}, n.constraints = {}, n.prototype.send = function (e, t) {
                return this._channelReady ? (i("send %s", e), this._channel.send(c.strict(e) || e instanceof ArrayBuffer || e instanceof Blob || "string" == typeof e ? e : JSON.stringify(e)), void(t && t(null))) : this.once("ready", this.send.bind(this, e, t))
            }, n.prototype.signal = function (e) {
                if (!this.destroyed) {
                    if ("string" == typeof e)try {
                        e = JSON.parse(e)
                    } catch (t) {
                        e = {}
                    }
                    if (i("signal %s", JSON.stringify(e)), e.sdp && this._pc.setRemoteDescription(new p(e), function () {
                            var e = "offer" === this._pc.remoteDescription.type;
                            e && this._pc.createAnswer(function (e) {
                                this._pc.setLocalDescription(e);
                                var t = function () {
                                    this.emit("signal", this._pc.localDescription || e)
                                }.bind(this);
                                this.trickle || this._iceComplete ? t() : this.once("_iceComplete", t)
                            }.bind(this), this._onError.bind(this))
                        }.bind(this), this._onError.bind(this)), e.candidate)try {
                        this._pc.addIceCandidate(new g(e.candidate))
                    } catch (t) {
                        this.destroy(new Error("error adding candidate, " + t.message))
                    }
                    e.sdp || e.candidate || this.destroy(new Error("signal() called with invalid signal data"))
                }
            }, n.prototype.destroy = function (e, t) {
                if (!this.destroyed) {
                    if (i("destroy (error: %s)", e && e.message), this.destroyed = !0, this.ready = !1, "function" == typeof e && (t = e, e = null), t && this.once("close", t), this._pc) {
                        try {
                            this._pc.close()
                        } catch (e) {
                        }
                        this._pc.oniceconnectionstatechange = null, this._pc.onsignalingstatechange = null, this._pc.onicecandidate = null
                    }
                    if (this._channel) {
                        try {
                            this._channel.close()
                        } catch (e) {
                        }
                        this._channel.onmessage = null, this._channel.onopen = null, this._channel.onclose = null
                    }
                    this._pc = null, this._channel = null, this._dataStreams.forEach(function (t) {
                        e && t.emit("error", e), t._readableState.ended || t.push(null), t._writableState.finished || t.end()
                    }), this._dataStreams = [], e && this.emit("error", e), this.emit("close")
                }
            }, n.prototype.getDataStream = function (e) {
                if (this.destroyed)throw new Error("peer is destroyed");
                var t = new r(s({_peer: this}, e));
                return this._dataStreams.push(t), t
            }, n.prototype._setupData = function (e) {
                this._channel = e.channel, this.channelName = this._channel.label, this._channel.binaryType = "arraybuffer", this._channel.onmessage = this._onChannelMessage.bind(this), this._channel.onopen = this._onChannelOpen.bind(this), this._channel.onclose = this._onChannelClose.bind(this)
            }, n.prototype._setupVideo = function (e) {
                this._pc.addStream(e), this._pc.onaddstream = this._onAddStream.bind(this)
            }, n.prototype._onIceConnectionStateChange = function () {
                var e = this._pc.iceGatheringState, t = this._pc.iceConnectionState;
                this.emit("iceConnectionStateChange", e, t), i("iceConnectionStateChange %s %s", e, t), ("connected" === t || "completed" === t) && (this._pcReady = !0, this._maybeReady()), ("disconnected" === t || "closed" === t) && this.destroy()
            }, n.prototype._maybeReady = function () {
                i("maybeReady pc %s channel %s", this._pcReady, this._channelReady), !this.ready && this._pcReady && this._channelReady && (i("ready"), this.ready = !0, this.emit("ready"))
            }, n.prototype._onSignalingStateChange = function () {
                this.emit("signalingStateChange", this._pc.signalingState), i("signalingStateChange %s", this._pc.signalingState)
            }, n.prototype._onIceCandidate = function (e) {
                e.candidate && this.trickle ? this.emit("signal", {candidate: e.candidate}) : e.candidate || (this._iceComplete = !0, this.emit("_iceComplete"))
            }, n.prototype._onChannelMessage = function (e) {
                if (!this.destroyed) {
                    var t = e.data;
                    if (i("receive %s", t), t instanceof ArrayBuffer)t = l(new Uint8Array(t)), this.emit("message", t); else try {
                        this.emit("message", JSON.parse(t))
                    } catch (n) {
                        this.emit("message", t)
                    }
                    this._dataStreams.forEach(function (e) {
                        e.push(t)
                    })
                }
            }, n.prototype._onChannelOpen = function () {
                this._channelReady = !0, this._maybeReady()
            }, n.prototype._onChannelClose = function () {
                this._channelReady = !1, this.destroy()
            }, n.prototype._onAddStream = function (e) {
                this.emit("stream", e.stream)
            }, n.prototype._onError = function (e) {
                i("error %s", e.message), this.destroy(e)
            }, u(r, f.Duplex), r.prototype.destroy = function () {
                this._peer.destroy()
            }, r.prototype._read = function () {
            }, r.prototype._write = function (e, t, n) {
                this._peer.send(e, n)
            }
        }, {
            debug: 20,
            events: 4,
            "extend.js": 23,
            hat: 24,
            inherits: 25,
            "is-typedarray": 26,
            once: 27,
            stream: 19,
            "typedarray-to-buffer": 28
        }],
        1: [function (e, t, n) {
            function r(e, t, n) {
                if (!(this instanceof r))return new r(e, t, n);
                var i, o = typeof e;
                if ("number" === o)i = e > 0 ? e >>> 0 : 0; else if ("string" === o)"base64" === t && (e = A(e)), i = r.byteLength(e, t); else {
                    if ("object" !== o || null === e)throw new Error("First argument needs to be a number, array or string.");
                    "Buffer" === e.type && B(e.data) && (e = e.data), i = +e.length > 0 ? Math.floor(+e.length) : 0
                }
                var s;
                H ? s = r._augment(new Uint8Array(i)) : (s = this, s.length = i, s._isBuffer = !0);
                var a;
                if (H && "number" == typeof e.byteLength)s._set(e); else if (x(e))if (r.isBuffer(e))for (a = 0; i > a; a++)s[a] = e.readUInt8(a); else for (a = 0; i > a; a++)s[a] = (e[a] % 256 + 256) % 256; else if ("string" === o)s.write(e, 0, t); else if ("number" === o && !H && !n)for (a = 0; i > a; a++)s[a] = 0;
                return s
            }

            function i(e, t, n, r) {
                n = Number(n) || 0;
                var i = e.length - n;
                r ? (r = Number(r), r > i && (r = i)) : r = i;
                var o = t.length;
                z(o % 2 === 0, "Invalid hex string"), r > o / 2 && (r = o / 2);
                for (var s = 0; r > s; s++) {
                    var a = parseInt(t.substr(2 * s, 2), 16);
                    z(!isNaN(a), "Invalid hex string"), e[n + s] = a
                }
                return s
            }

            function o(e, t, n, r) {
                var i = N(R(t), e, n, r);
                return i
            }

            function s(e, t, n, r) {
                var i = N(T(t), e, n, r);
                return i
            }

            function a(e, t, n, r) {
                return s(e, t, n, r)
            }

            function u(e, t, n, r) {
                var i = N(D(t), e, n, r);
                return i
            }

            function c(e, t, n, r) {
                var i = N(U(t), e, n, r);
                return i
            }

            function h(e, t, n) {
                return J.fromByteArray(0 === t && n === e.length ? e : e.slice(t, n))
            }

            function f(e, t, n) {
                var r = "", i = "";
                n = Math.min(e.length, n);
                for (var o = t; n > o; o++)e[o] <= 127 ? (r += O(i) + String.fromCharCode(e[o]), i = "") : i += "%" + e[o].toString(16);
                return r + O(i)
            }

            function l(e, t, n) {
                var r = "";
                n = Math.min(e.length, n);
                for (var i = t; n > i; i++)r += String.fromCharCode(e[i]);
                return r
            }

            function d(e, t, n) {
                return l(e, t, n)
            }

            function p(e, t, n) {
                var r = e.length;
                (!t || 0 > t) && (t = 0), (!n || 0 > n || n > r) && (n = r);
                for (var i = "", o = t; n > o; o++)i += j(e[o]);
                return i
            }

            function g(e, t, n) {
                for (var r = e.slice(t, n), i = "", o = 0; o < r.length; o += 2)i += String.fromCharCode(r[o] + 256 * r[o + 1]);
                return i
            }

            function m(e, t, n, r) {
                r || (z("boolean" == typeof n, "missing or invalid endian"), z(void 0 !== t && null !== t, "missing offset"), z(t + 1 < e.length, "Trying to read beyond buffer length"));
                var i = e.length;
                if (!(t >= i)) {
                    var o;
                    return n ? (o = e[t], i > t + 1 && (o |= e[t + 1] << 8)) : (o = e[t] << 8, i > t + 1 && (o |= e[t + 1])), o
                }
            }

            function v(e, t, n, r) {
                r || (z("boolean" == typeof n, "missing or invalid endian"), z(void 0 !== t && null !== t, "missing offset"), z(t + 3 < e.length, "Trying to read beyond buffer length"));
                var i = e.length;
                if (!(t >= i)) {
                    var o;
                    return n ? (i > t + 2 && (o = e[t + 2] << 16), i > t + 1 && (o |= e[t + 1] << 8), o |= e[t], i > t + 3 && (o += e[t + 3] << 24 >>> 0)) : (i > t + 1 && (o = e[t + 1] << 16), i > t + 2 && (o |= e[t + 2] << 8), i > t + 3 && (o |= e[t + 3]), o += e[t] << 24 >>> 0), o
                }
            }

            function b(e, t, n, r) {
                r || (z("boolean" == typeof n, "missing or invalid endian"), z(void 0 !== t && null !== t, "missing offset"), z(t + 1 < e.length, "Trying to read beyond buffer length"));
                var i = e.length;
                if (!(t >= i)) {
                    var o = m(e, t, n, !0), s = 32768 & o;
                    return s ? -1 * (65535 - o + 1) : o
                }
            }

            function y(e, t, n, r) {
                r || (z("boolean" == typeof n, "missing or invalid endian"), z(void 0 !== t && null !== t, "missing offset"), z(t + 3 < e.length, "Trying to read beyond buffer length"));
                var i = e.length;
                if (!(t >= i)) {
                    var o = v(e, t, n, !0), s = 2147483648 & o;
                    return s ? -1 * (4294967295 - o + 1) : o
                }
            }

            function w(e, t, n, r) {
                return r || (z("boolean" == typeof n, "missing or invalid endian"), z(t + 3 < e.length, "Trying to read beyond buffer length")), q.read(e, t, n, 23, 4)
            }

            function _(e, t, n, r) {
                return r || (z("boolean" == typeof n, "missing or invalid endian"), z(t + 7 < e.length, "Trying to read beyond buffer length")), q.read(e, t, n, 52, 8)
            }

            function E(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 1 < e.length, "trying to write beyond buffer length"), F(t, 65535));
                var o = e.length;
                if (!(n >= o)) {
                    for (var s = 0, a = Math.min(o - n, 2); a > s; s++)e[n + s] = (t & 255 << 8 * (r ? s : 1 - s)) >>> 8 * (r ? s : 1 - s);
                    return n + 2
                }
            }

            function S(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 3 < e.length, "trying to write beyond buffer length"), F(t, 4294967295));
                var o = e.length;
                if (!(n >= o)) {
                    for (var s = 0, a = Math.min(o - n, 4); a > s; s++)e[n + s] = t >>> 8 * (r ? s : 3 - s) & 255;
                    return n + 4
                }
            }

            function L(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 1 < e.length, "Trying to write beyond buffer length"), W(t, 32767, -32768));
                var o = e.length;
                if (!(n >= o))return t >= 0 ? E(e, t, n, r, i) : E(e, 65535 + t + 1, n, r, i), n + 2
            }

            function C(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 3 < e.length, "Trying to write beyond buffer length"), W(t, 2147483647, -2147483648));
                var o = e.length;
                if (!(n >= o))return t >= 0 ? S(e, t, n, r, i) : S(e, 4294967295 + t + 1, n, r, i), n + 4
            }

            function k(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 3 < e.length, "Trying to write beyond buffer length"), P(t, 3.4028234663852886e38, -3.4028234663852886e38));
                var o = e.length;
                if (!(n >= o))return q.write(e, t, n, r, 23, 4), n + 4
            }

            function I(e, t, n, r, i) {
                i || (z(void 0 !== t && null !== t, "missing value"), z("boolean" == typeof r, "missing or invalid endian"), z(void 0 !== n && null !== n, "missing offset"), z(n + 7 < e.length, "Trying to write beyond buffer length"), P(t, 1.7976931348623157e308, -1.7976931348623157e308));
                var o = e.length;
                if (!(n >= o))return q.write(e, t, n, r, 52, 8), n + 8
            }

            function A(e) {
                for (e = M(e).replace(V, ""); e.length % 4 !== 0;)e += "=";
                return e
            }

            function M(e) {
                return e.trim ? e.trim() : e.replace(/^\s+|\s+$/g, "")
            }

            function B(e) {
                return (Array.isArray || function (e) {
                    return "[object Array]" === Object.prototype.toString.call(e)
                })(e)
            }

            function x(e) {
                return B(e) || r.isBuffer(e) || e && "object" == typeof e && "number" == typeof e.length
            }

            function j(e) {
                return 16 > e ? "0" + e.toString(16) : e.toString(16)
            }

            function R(e) {
                for (var t = [], n = 0; n < e.length; n++) {
                    var r = e.charCodeAt(n);
                    if (127 >= r)t.push(r); else {
                        var i = n;
                        r >= 55296 && 57343 >= r && n++;
                        for (var o = encodeURIComponent(e.slice(i, n + 1)).substr(1).split("%"), s = 0; s < o.length; s++)t.push(parseInt(o[s], 16))
                    }
                }
                return t
            }

            function T(e) {
                for (var t = [], n = 0; n < e.length; n++)t.push(255 & e.charCodeAt(n));
                return t
            }

            function U(e) {
                for (var t, n, r, i = [], o = 0; o < e.length; o++)t = e.charCodeAt(o), n = t >> 8, r = t % 256, i.push(r), i.push(n);
                return i
            }

            function D(e) {
                return J.toByteArray(e)
            }

            function N(e, t, n, r) {
                for (var i = 0; r > i && !(i + n >= t.length || i >= e.length); i++)t[i + n] = e[i];
                return i
            }

            function O(e) {
                try {
                    return decodeURIComponent(e)
                } catch (t) {
                    return String.fromCharCode(65533)
                }
            }

            function F(e, t) {
                z("number" == typeof e, "cannot write a non-number as a number"), z(e >= 0, "specified a negative value for writing an unsigned value"), z(t >= e, "value is larger than maximum value for type"), z(Math.floor(e) === e, "value has a fractional component")
            }

            function W(e, t, n) {
                z("number" == typeof e, "cannot write a non-number as a number"), z(t >= e, "value larger than maximum allowed value"), z(e >= n, "value smaller than minimum allowed value"), z(Math.floor(e) === e, "value has a fractional component")
            }

            function P(e, t, n) {
                z("number" == typeof e, "cannot write a non-number as a number"), z(t >= e, "value larger than maximum allowed value"), z(e >= n, "value smaller than minimum allowed value")
            }

            function z(e, t) {
                if (!e)throw new Error(t || "Failed assertion")
            }

            var J = e("base64-js"), q = e("ieee754");
            n.Buffer = r, n.SlowBuffer = r, n.INSPECT_MAX_BYTES = 50, r.poolSize = 8192;
            var H = function () {
                try {
                    var e = new ArrayBuffer(0), t = new Uint8Array(e);
                    return t.foo = function () {
                        return 42
                    }, 42 === t.foo() && "function" == typeof t.subarray && 0 === new Uint8Array(1).subarray(1, 1).byteLength
                } catch (n) {
                    return !1
                }
            }();
            r.isEncoding = function (e) {
                switch (String(e).toLowerCase()) {
                    case"hex":
                    case"utf8":
                    case"utf-8":
                    case"ascii":
                    case"binary":
                    case"base64":
                    case"raw":
                    case"ucs2":
                    case"ucs-2":
                    case"utf16le":
                    case"utf-16le":
                        return !0;
                    default:
                        return !1
                }
            }, r.isBuffer = function (e) {
                return !(null == e || !e._isBuffer)
            }, r.byteLength = function (e, t) {
                var n;
                switch (e = e.toString(), t || "utf8") {
                    case"hex":
                        n = e.length / 2;
                        break;
                    case"utf8":
                    case"utf-8":
                        n = R(e).length;
                        break;
                    case"ascii":
                    case"binary":
                    case"raw":
                        n = e.length;
                        break;
                    case"base64":
                        n = D(e).length;
                        break;
                    case"ucs2":
                    case"ucs-2":
                    case"utf16le":
                    case"utf-16le":
                        n = 2 * e.length;
                        break;
                    default:
                        throw new Error("Unknown encoding")
                }
                return n
            }, r.concat = function (e, t) {
                if (z(B(e), "Usage: Buffer.concat(list[, length])"), 0 === e.length)return new r(0);
                if (1 === e.length)return e[0];
                var n;
                if (void 0 === t)for (t = 0, n = 0; n < e.length; n++)t += e[n].length;
                var i = new r(t), o = 0;
                for (n = 0; n < e.length; n++) {
                    var s = e[n];
                    s.copy(i, o), o += s.length
                }
                return i
            }, r.compare = function (e, t) {
                z(r.isBuffer(e) && r.isBuffer(t), "Arguments must be Buffers");
                for (var n = e.length, i = t.length, o = 0, s = Math.min(n, i); s > o && e[o] === t[o]; o++);
                return o !== s && (n = e[o], i = t[o]), i > n ? -1 : n > i ? 1 : 0
            }, r.prototype.write = function (e, t, n, r) {
                if (isFinite(t))isFinite(n) || (r = n, n = void 0); else {
                    var h = r;
                    r = t, t = n, n = h
                }
                t = Number(t) || 0;
                var f = this.length - t;
                n ? (n = Number(n), n > f && (n = f)) : n = f, r = String(r || "utf8").toLowerCase();
                var l;
                switch (r) {
                    case"hex":
                        l = i(this, e, t, n);
                        break;
                    case"utf8":
                    case"utf-8":
                        l = o(this, e, t, n);
                        break;
                    case"ascii":
                        l = s(this, e, t, n);
                        break;
                    case"binary":
                        l = a(this, e, t, n);
                        break;
                    case"base64":
                        l = u(this, e, t, n);
                        break;
                    case"ucs2":
                    case"ucs-2":
                    case"utf16le":
                    case"utf-16le":
                        l = c(this, e, t, n);
                        break;
                    default:
                        throw new Error("Unknown encoding")
                }
                return l
            }, r.prototype.toString = function (e, t, n) {
                var r = this;
                if (e = String(e || "utf8").toLowerCase(), t = Number(t) || 0, n = void 0 === n ? r.length : Number(n), n === t)return "";
                var i;
                switch (e) {
                    case"hex":
                        i = p(r, t, n);
                        break;
                    case"utf8":
                    case"utf-8":
                        i = f(r, t, n);
                        break;
                    case"ascii":
                        i = l(r, t, n);
                        break;
                    case"binary":
                        i = d(r, t, n);
                        break;
                    case"base64":
                        i = h(r, t, n);
                        break;
                    case"ucs2":
                    case"ucs-2":
                    case"utf16le":
                    case"utf-16le":
                        i = g(r, t, n);
                        break;
                    default:
                        throw new Error("Unknown encoding")
                }
                return i
            }, r.prototype.toJSON = function () {
                return {type: "Buffer", data: Array.prototype.slice.call(this._arr || this, 0)}
            }, r.prototype.equals = function (e) {
                return z(r.isBuffer(e), "Argument must be a Buffer"), 0 === r.compare(this, e)
            }, r.prototype.compare = function (e) {
                return z(r.isBuffer(e), "Argument must be a Buffer"), r.compare(this, e)
            }, r.prototype.copy = function (e, t, n, r) {
                var i = this;
                if (n || (n = 0), r || 0 === r || (r = this.length), t || (t = 0), r !== n && 0 !== e.length && 0 !== i.length) {
                    z(r >= n, "sourceEnd < sourceStart"), z(t >= 0 && t < e.length, "targetStart out of bounds"), z(n >= 0 && n < i.length, "sourceStart out of bounds"), z(r >= 0 && r <= i.length, "sourceEnd out of bounds"), r > this.length && (r = this.length), e.length - t < r - n && (r = e.length - t + n);
                    var o = r - n;
                    if (100 > o || !H)for (var s = 0; o > s; s++)e[s + t] = this[s + n]; else e._set(this.subarray(n, n + o), t)
                }
            }, r.prototype.slice = function (e, t) {
                var n = this.length;
                if (e = ~~e, t = void 0 === t ? n : ~~t, 0 > e ? (e += n, 0 > e && (e = 0)) : e > n && (e = n), 0 > t ? (t += n, 0 > t && (t = 0)) : t > n && (t = n), e > t && (t = e), H)return r._augment(this.subarray(e, t));
                for (var i = t - e, o = new r(i, void 0, !0), s = 0; i > s; s++)o[s] = this[s + e];
                return o
            }, r.prototype.get = function (e) {
                return console.log(".get() is deprecated. Access using array indexes instead."), this.readUInt8(e)
            }, r.prototype.set = function (e, t) {
                return console.log(".set() is deprecated. Access using array indexes instead."), this.writeUInt8(e, t)
            }, r.prototype.readUInt8 = function (e, t) {
                return t || (z(void 0 !== e && null !== e, "missing offset"), z(e < this.length, "Trying to read beyond buffer length")), e >= this.length ? void 0 : this[e]
            }, r.prototype.readUInt16LE = function (e, t) {
                return m(this, e, !0, t)
            }, r.prototype.readUInt16BE = function (e, t) {
                return m(this, e, !1, t)
            }, r.prototype.readUInt32LE = function (e, t) {
                return v(this, e, !0, t)
            }, r.prototype.readUInt32BE = function (e, t) {
                return v(this, e, !1, t)
            }, r.prototype.readInt8 = function (e, t) {
                if (t || (z(void 0 !== e && null !== e, "missing offset"), z(e < this.length, "Trying to read beyond buffer length")), !(e >= this.length)) {
                    var n = 128 & this[e];
                    return n ? -1 * (255 - this[e] + 1) : this[e]
                }
            }, r.prototype.readInt16LE = function (e, t) {
                return b(this, e, !0, t)
            }, r.prototype.readInt16BE = function (e, t) {
                return b(this, e, !1, t)
            }, r.prototype.readInt32LE = function (e, t) {
                return y(this, e, !0, t)
            }, r.prototype.readInt32BE = function (e, t) {
                return y(this, e, !1, t)
            }, r.prototype.readFloatLE = function (e, t) {
                return w(this, e, !0, t)
            }, r.prototype.readFloatBE = function (e, t) {
                return w(this, e, !1, t)
            }, r.prototype.readDoubleLE = function (e, t) {
                return _(this, e, !0, t)
            }, r.prototype.readDoubleBE = function (e, t) {
                return _(this, e, !1, t)
            }, r.prototype.writeUInt8 = function (e, t, n) {
                return n || (z(void 0 !== e && null !== e, "missing value"), z(void 0 !== t && null !== t, "missing offset"), z(t < this.length, "trying to write beyond buffer length"), F(e, 255)), t >= this.length ? void 0 : (this[t] = e, t + 1)
            }, r.prototype.writeUInt16LE = function (e, t, n) {
                return E(this, e, t, !0, n)
            }, r.prototype.writeUInt16BE = function (e, t, n) {
                return E(this, e, t, !1, n)
            }, r.prototype.writeUInt32LE = function (e, t, n) {
                return S(this, e, t, !0, n)
            }, r.prototype.writeUInt32BE = function (e, t, n) {
                return S(this, e, t, !1, n)
            }, r.prototype.writeInt8 = function (e, t, n) {
                return n || (z(void 0 !== e && null !== e, "missing value"), z(void 0 !== t && null !== t, "missing offset"), z(t < this.length, "Trying to write beyond buffer length"), W(e, 127, -128)), t >= this.length ? void 0 : (e >= 0 ? this.writeUInt8(e, t, n) : this.writeUInt8(255 + e + 1, t, n), t + 1)
            }, r.prototype.writeInt16LE = function (e, t, n) {
                return L(this, e, t, !0, n)
            }, r.prototype.writeInt16BE = function (e, t, n) {
                return L(this, e, t, !1, n)
            }, r.prototype.writeInt32LE = function (e, t, n) {
                return C(this, e, t, !0, n)
            }, r.prototype.writeInt32BE = function (e, t, n) {
                return C(this, e, t, !1, n)
            }, r.prototype.writeFloatLE = function (e, t, n) {
                return k(this, e, t, !0, n)
            }, r.prototype.writeFloatBE = function (e, t, n) {
                return k(this, e, t, !1, n)
            }, r.prototype.writeDoubleLE = function (e, t, n) {
                return I(this, e, t, !0, n)
            }, r.prototype.writeDoubleBE = function (e, t, n) {
                return I(this, e, t, !1, n)
            }, r.prototype.fill = function (e, t, n) {
                if (e || (e = 0), t || (t = 0), n || (n = this.length), z(n >= t, "end < start"), n !== t && 0 !== this.length) {
                    z(t >= 0 && t < this.length, "start out of bounds"), z(n >= 0 && n <= this.length, "end out of bounds");
                    var r;
                    if ("number" == typeof e)for (r = t; n > r; r++)this[r] = e; else {
                        var i = R(e.toString()), o = i.length;
                        for (r = t; n > r; r++)this[r] = i[r % o]
                    }
                    return this
                }
            }, r.prototype.inspect = function () {
                for (var e = [], t = this.length, r = 0; t > r; r++)if (e[r] = j(this[r]), r === n.INSPECT_MAX_BYTES) {
                    e[r + 1] = "...";
                    break
                }
                return "<Buffer " + e.join(" ") + ">"
            }, r.prototype.toArrayBuffer = function () {
                if ("undefined" != typeof Uint8Array) {
                    if (H)return new r(this).buffer;
                    for (var e = new Uint8Array(this.length), t = 0, n = e.length; n > t; t += 1)e[t] = this[t];
                    return e.buffer
                }
                throw new Error("Buffer.toArrayBuffer not supported in this browser")
            };
            var $ = r.prototype;
            r._augment = function (e) {
                return e._isBuffer = !0, e._get = e.get, e._set = e.set, e.get = $.get, e.set = $.set, e.write = $.write, e.toString = $.toString, e.toLocaleString = $.toString, e.toJSON = $.toJSON, e.equals = $.equals, e.compare = $.compare, e.copy = $.copy, e.slice = $.slice, e.readUInt8 = $.readUInt8, e.readUInt16LE = $.readUInt16LE, e.readUInt16BE = $.readUInt16BE, e.readUInt32LE = $.readUInt32LE, e.readUInt32BE = $.readUInt32BE, e.readInt8 = $.readInt8, e.readInt16LE = $.readInt16LE, e.readInt16BE = $.readInt16BE, e.readInt32LE = $.readInt32LE, e.readInt32BE = $.readInt32BE, e.readFloatLE = $.readFloatLE, e.readFloatBE = $.readFloatBE, e.readDoubleLE = $.readDoubleLE, e.readDoubleBE = $.readDoubleBE, e.writeUInt8 = $.writeUInt8, e.writeUInt16LE = $.writeUInt16LE, e.writeUInt16BE = $.writeUInt16BE, e.writeUInt32LE = $.writeUInt32LE, e.writeUInt32BE = $.writeUInt32BE, e.writeInt8 = $.writeInt8, e.writeInt16LE = $.writeInt16LE, e.writeInt16BE = $.writeInt16BE, e.writeInt32LE = $.writeInt32LE, e.writeInt32BE = $.writeInt32BE, e.writeFloatLE = $.writeFloatLE, e.writeFloatBE = $.writeFloatBE, e.writeDoubleLE = $.writeDoubleLE, e.writeDoubleBE = $.writeDoubleBE, e.fill = $.fill, e.inspect = $.inspect, e.toArrayBuffer = $.toArrayBuffer, e
            };
            var V = /[^+\/0-9A-z]/g
        }, {"base64-js": 2, ieee754: 3}],
        2: [function (e, t, n) {
            var r = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            !function (e) {
                "use strict";
                function t(e) {
                    var t = e.charCodeAt(0);
                    return t === s ? 62 : t === a ? 63 : u > t ? -1 : u + 10 > t ? t - u + 26 + 26 : h + 26 > t ? t - h : c + 26 > t ? t - c + 26 : void 0
                }

                function n(e) {
                    function n(e) {
                        c[f++] = e
                    }

                    var r, i, s, a, u, c;
                    if (e.length % 4 > 0)throw new Error("Invalid string. Length must be a multiple of 4");
                    var h = e.length;
                    u = "=" === e.charAt(h - 2) ? 2 : "=" === e.charAt(h - 1) ? 1 : 0, c = new o(3 * e.length / 4 - u), s = u > 0 ? e.length - 4 : e.length;
                    var f = 0;
                    for (r = 0, i = 0; s > r; r += 4, i += 3)a = t(e.charAt(r)) << 18 | t(e.charAt(r + 1)) << 12 | t(e.charAt(r + 2)) << 6 | t(e.charAt(r + 3)), n((16711680 & a) >> 16), n((65280 & a) >> 8), n(255 & a);
                    return 2 === u ? (a = t(e.charAt(r)) << 2 | t(e.charAt(r + 1)) >> 4, n(255 & a)) : 1 === u && (a = t(e.charAt(r)) << 10 | t(e.charAt(r + 1)) << 4 | t(e.charAt(r + 2)) >> 2, n(a >> 8 & 255), n(255 & a)), c
                }

                function i(e) {
                    function t(e) {
                        return r.charAt(e)
                    }

                    function n(e) {
                        return t(e >> 18 & 63) + t(e >> 12 & 63) + t(e >> 6 & 63) + t(63 & e)
                    }

                    var i, o, s, a = e.length % 3, u = "";
                    for (i = 0, s = e.length - a; s > i; i += 3)o = (e[i] << 16) + (e[i + 1] << 8) + e[i + 2], u += n(o);
                    switch (a) {
                        case 1:
                            o = e[e.length - 1], u += t(o >> 2), u += t(o << 4 & 63), u += "==";
                            break;
                        case 2:
                            o = (e[e.length - 2] << 8) + e[e.length - 1], u += t(o >> 10), u += t(o >> 4 & 63), u += t(o << 2 & 63), u += "="
                    }
                    return u
                }

                var o = "undefined" != typeof Uint8Array ? Uint8Array : Array, s = "+".charCodeAt(0), a = "/".charCodeAt(0), u = "0".charCodeAt(0), c = "a".charCodeAt(0), h = "A".charCodeAt(0);
                e.toByteArray = n, e.fromByteArray = i
            }("undefined" == typeof n ? this.base64js = {} : n)
        }, {}],
        3: [function (e, t, n) {
            n.read = function (e, t, n, r, i) {
                var o, s, a = 8 * i - r - 1, u = (1 << a) - 1, c = u >> 1, h = -7, f = n ? i - 1 : 0, l = n ? -1 : 1, d = e[t + f];
                for (f += l, o = d & (1 << -h) - 1, d >>= -h, h += a; h > 0; o = 256 * o + e[t + f], f += l, h -= 8);
                for (s = o & (1 << -h) - 1, o >>= -h, h += r; h > 0; s = 256 * s + e[t + f], f += l, h -= 8);
                if (0 === o)o = 1 - c; else {
                    if (o === u)return s ? 0 / 0 : 1 / 0 * (d ? -1 : 1);
                    s += Math.pow(2, r), o -= c
                }
                return (d ? -1 : 1) * s * Math.pow(2, o - r)
            }, n.write = function (e, t, n, r, i, o) {
                var s, a, u, c = 8 * o - i - 1, h = (1 << c) - 1, f = h >> 1, l = 23 === i ? Math.pow(2, -24) - Math.pow(2, -77) : 0, d = r ? 0 : o - 1, p = r ? 1 : -1, g = 0 > t || 0 === t && 0 > 1 / t ? 1 : 0;
                for (t = Math.abs(t), isNaN(t) || 1 / 0 === t ? (a = isNaN(t) ? 1 : 0, s = h) : (s = Math.floor(Math.log(t) / Math.LN2), t * (u = Math.pow(2, -s)) < 1 && (s--, u *= 2), t += s + f >= 1 ? l / u : l * Math.pow(2, 1 - f), t * u >= 2 && (s++, u /= 2), s + f >= h ? (a = 0, s = h) : s + f >= 1 ? (a = (t * u - 1) * Math.pow(2, i), s += f) : (a = t * Math.pow(2, f - 1) * Math.pow(2, i), s = 0)); i >= 8; e[n + d] = 255 & a, d += p, a /= 256, i -= 8);
                for (s = s << i | a, c += i; c > 0; e[n + d] = 255 & s, d += p, s /= 256, c -= 8);
                e[n + d - p] |= 128 * g
            }
        }, {}],
        4: [function (e, t) {
            function n() {
                this._events = this._events || {}, this._maxListeners = this._maxListeners || void 0
            }

            function r(e) {
                return "function" == typeof e
            }

            function i(e) {
                return "number" == typeof e
            }

            function o(e) {
                return "object" == typeof e && null !== e
            }

            function s(e) {
                return void 0 === e
            }

            t.exports = n, n.EventEmitter = n, n.prototype._events = void 0, n.prototype._maxListeners = void 0, n.defaultMaxListeners = 10, n.prototype.setMaxListeners = function (e) {
                if (!i(e) || 0 > e || isNaN(e))throw TypeError("n must be a positive number");
                return this._maxListeners = e, this
            }, n.prototype.emit = function (e) {
                var t, n, i, a, u, c;
                if (this._events || (this._events = {}), "error" === e && (!this._events.error || o(this._events.error) && !this._events.error.length))throw t = arguments[1], t instanceof Error ? t : TypeError('Uncaught, unspecified "error" event.');
                if (n = this._events[e], s(n))return !1;
                if (r(n))switch (arguments.length) {
                    case 1:
                        n.call(this);
                        break;
                    case 2:
                        n.call(this, arguments[1]);
                        break;
                    case 3:
                        n.call(this, arguments[1], arguments[2]);
                        break;
                    default:
                        for (i = arguments.length, a = new Array(i - 1), u = 1; i > u; u++)a[u - 1] = arguments[u];
                        n.apply(this, a)
                } else if (o(n)) {
                    for (i = arguments.length, a = new Array(i - 1), u = 1; i > u; u++)a[u - 1] = arguments[u];
                    for (c = n.slice(), i = c.length, u = 0; i > u; u++)c[u].apply(this, a)
                }
                return !0
            }, n.prototype.addListener = function (e, t) {
                var i;
                if (!r(t))throw TypeError("listener must be a function");
                if (this._events || (this._events = {}), this._events.newListener && this.emit("newListener", e, r(t.listener) ? t.listener : t), this._events[e] ? o(this._events[e]) ? this._events[e].push(t) : this._events[e] = [this._events[e], t] : this._events[e] = t, o(this._events[e]) && !this._events[e].warned) {
                    var i;
                    i = s(this._maxListeners) ? n.defaultMaxListeners : this._maxListeners, i && i > 0 && this._events[e].length > i && (this._events[e].warned = !0, console.error("(node) warning: possible EventEmitter memory leak detected. %d listeners added. Use emitter.setMaxListeners() to increase limit.", this._events[e].length), "function" == typeof console.trace && console.trace())
                }
                return this
            }, n.prototype.on = n.prototype.addListener, n.prototype.once = function (e, t) {
                function n() {
                    this.removeListener(e, n), i || (i = !0, t.apply(this, arguments))
                }

                if (!r(t))throw TypeError("listener must be a function");
                var i = !1;
                return n.listener = t, this.on(e, n), this
            }, n.prototype.removeListener = function (e, t) {
                var n, i, s, a;
                if (!r(t))throw TypeError("listener must be a function");
                if (!this._events || !this._events[e])return this;
                if (n = this._events[e], s = n.length, i = -1, n === t || r(n.listener) && n.listener === t)delete this._events[e], this._events.removeListener && this.emit("removeListener", e, t); else if (o(n)) {
                    for (a = s; a-- > 0;)if (n[a] === t || n[a].listener && n[a].listener === t) {
                        i = a;
                        break
                    }
                    if (0 > i)return this;
                    1 === n.length ? (n.length = 0, delete this._events[e]) : n.splice(i, 1), this._events.removeListener && this.emit("removeListener", e, t)
                }
                return this
            }, n.prototype.removeAllListeners = function (e) {
                var t, n;
                if (!this._events)return this;
                if (!this._events.removeListener)return 0 === arguments.length ? this._events = {} : this._events[e] && delete this._events[e], this;
                if (0 === arguments.length) {
                    for (t in this._events)"removeListener" !== t && this.removeAllListeners(t);
                    return this.removeAllListeners("removeListener"), this._events = {}, this
                }
                if (n = this._events[e], r(n))this.removeListener(e, n); else for (; n.length;)this.removeListener(e, n[n.length - 1]);
                return delete this._events[e], this
            }, n.prototype.listeners = function (e) {
                var t;
                return t = this._events && this._events[e] ? r(this._events[e]) ? [this._events[e]] : this._events[e].slice() : []
            }, n.listenerCount = function (e, t) {
                var n;
                return n = e._events && e._events[t] ? r(e._events[t]) ? 1 : e._events[t].length : 0
            }
        }, {}],
        5: [function (e, t) {
            t.exports = Array.isArray || function (e) {
                    return "[object Array]" == Object.prototype.toString.call(e)
                }
        }, {}],
        6: [function (e, t) {
            function n() {
            }

            var r = t.exports = {};
            r.nextTick = function () {
                var e = "undefined" != typeof window && window.setImmediate, t = "undefined" != typeof window && window.postMessage && window.addEventListener;
                if (e)return function (e) {
                    return window.setImmediate(e)
                };
                if (t) {
                    var n = [];
                    return window.addEventListener("message", function (e) {
                        var t = e.source;
                        if ((t === window || null === t) && "process-tick" === e.data && (e.stopPropagation(), n.length > 0)) {
                            var r = n.shift();
                            r()
                        }
                    }, !0), function (e) {
                        n.push(e), window.postMessage("process-tick", "*")
                    }
                }
                return function (e) {
                    setTimeout(e, 0)
                }
            }(), r.title = "browser", r.browser = !0, r.env = {}, r.argv = [], r.on = n, r.addListener = n, r.once = n, r.off = n, r.removeListener = n, r.removeAllListeners = n, r.emit = n, r.binding = function () {
                throw new Error("process.binding is not supported")
            }, r.cwd = function () {
                return "/"
            }, r.chdir = function () {
                throw new Error("process.chdir is not supported")
            }
        }, {}],
        7: [function (e, t) {
            t.exports = e("./lib/_stream_duplex.js")
        }, {"./lib/_stream_duplex.js": 8}],
        8: [function (e, t) {
            (function (n) {
                function r(e) {
                    return this instanceof r ? (u.call(this, e), c.call(this, e), e && e.readable === !1 && (this.readable = !1), e && e.writable === !1 && (this.writable = !1), this.allowHalfOpen = !0, e && e.allowHalfOpen === !1 && (this.allowHalfOpen = !1), void this.once("end", i)) : new r(e)
                }

                function i() {
                    this.allowHalfOpen || this._writableState.ended || n.nextTick(this.end.bind(this))
                }

                function o(e, t) {
                    for (var n = 0, r = e.length; r > n; n++)t(e[n], n)
                }

                t.exports = r;
                var s = Object.keys || function (e) {
                        var t = [];
                        for (var n in e)t.push(n);
                        return t
                    }, a = e("core-util-is");
                a.inherits = e("inherits");
                var u = e("./_stream_readable"), c = e("./_stream_writable");
                a.inherits(r, u), o(s(c.prototype), function (e) {
                    r.prototype[e] || (r.prototype[e] = c.prototype[e])
                })
            }).call(this, e("_process"))
        }, {"./_stream_readable": 10, "./_stream_writable": 12, _process: 6, "core-util-is": 13, inherits: 25}],
        9: [function (e, t) {
            function n(e) {
                return this instanceof n ? void r.call(this, e) : new n(e)
            }

            t.exports = n;
            var r = e("./_stream_transform"), i = e("core-util-is");
            i.inherits = e("inherits"), i.inherits(n, r), n.prototype._transform = function (e, t, n) {
                n(null, e)
            }
        }, {"./_stream_transform": 11, "core-util-is": 13, inherits: 25}],
        10: [function (e, t) {
            (function (n) {
                function r(t) {
                    t = t || {};
                    var n = t.highWaterMark;
                    this.highWaterMark = n || 0 === n ? n : 16384, this.highWaterMark = ~~this.highWaterMark, this.buffer = [], this.length = 0, this.pipes = null, this.pipesCount = 0, this.flowing = !1, this.ended = !1, this.endEmitted = !1, this.reading = !1, this.calledRead = !1, this.sync = !0, this.needReadable = !1, this.emittedReadable = !1, this.readableListening = !1, this.objectMode = !!t.objectMode, this.defaultEncoding = t.defaultEncoding || "utf8", this.ranOut = !1, this.awaitDrain = 0, this.readingMore = !1, this.decoder = null, this.encoding = null, t.encoding && (A || (A = e("string_decoder/").StringDecoder), this.decoder = new A(t.encoding), this.encoding = t.encoding)
                }

                function i(e) {
                    return this instanceof i ? (this._readableState = new r(e, this), this.readable = !0, void k.call(this)) : new i(e)
                }

                function o(e, t, n, r, i) {
                    var o = c(t, n);
                    if (o)e.emit("error", o); else if (null === n || void 0 === n)t.reading = !1, t.ended || h(e, t); else if (t.objectMode || n && n.length > 0)if (t.ended && !i) {
                        var a = new Error("stream.push() after EOF");
                        e.emit("error", a)
                    } else if (t.endEmitted && i) {
                        var a = new Error("stream.unshift() after end event");
                        e.emit("error", a)
                    } else!t.decoder || i || r || (n = t.decoder.write(n)), t.length += t.objectMode ? 1 : n.length, i ? t.buffer.unshift(n) : (t.reading = !1, t.buffer.push(n)), t.needReadable && f(e), d(e, t); else i || (t.reading = !1);
                    return s(t)
                }

                function s(e) {
                    return !e.ended && (e.needReadable || e.length < e.highWaterMark || 0 === e.length)
                }

                function a(e) {
                    if (e >= M)e = M; else {
                        e--;
                        for (var t = 1; 32 > t; t <<= 1)e |= e >> t;
                        e++
                    }
                    return e
                }

                function u(e, t) {
                    return 0 === t.length && t.ended ? 0 : t.objectMode ? 0 === e ? 0 : 1 : isNaN(e) || null === e ? t.flowing && t.buffer.length ? t.buffer[0].length : t.length : 0 >= e ? 0 : (e > t.highWaterMark && (t.highWaterMark = a(e)), e > t.length ? t.ended ? t.length : (t.needReadable = !0, 0) : e)
                }

                function c(e, t) {
                    var n = null;
                    return L.isBuffer(t) || "string" == typeof t || null === t || void 0 === t || e.objectMode || n || (n = new TypeError("Invalid non-string/buffer chunk")), n
                }

                function h(e, t) {
                    if (t.decoder && !t.ended) {
                        var n = t.decoder.end();
                        n && n.length && (t.buffer.push(n), t.length += t.objectMode ? 1 : n.length)
                    }
                    t.ended = !0, t.length > 0 ? f(e) : w(e)
                }

                function f(e) {
                    var t = e._readableState;
                    t.needReadable = !1, t.emittedReadable || (t.emittedReadable = !0, t.sync ? n.nextTick(function () {
                        l(e)
                    }) : l(e))
                }

                function l(e) {
                    e.emit("readable")
                }

                function d(e, t) {
                    t.readingMore || (t.readingMore = !0, n.nextTick(function () {
                        p(e, t)
                    }))
                }

                function p(e, t) {
                    for (var n = t.length; !t.reading && !t.flowing && !t.ended && t.length < t.highWaterMark && (e.read(0), n !== t.length);)n = t.length;
                    t.readingMore = !1
                }

                function g(e) {
                    return function () {
                        var t = e._readableState;
                        t.awaitDrain--, 0 === t.awaitDrain && m(e)
                    }
                }

                function m(e) {
                    function t(e) {
                        var t = e.write(n);
                        !1 === t && r.awaitDrain++
                    }

                    var n, r = e._readableState;
                    for (r.awaitDrain = 0; r.pipesCount && null !== (n = e.read());)if (1 === r.pipesCount ? t(r.pipes, 0, null) : _(r.pipes, t), e.emit("data", n), r.awaitDrain > 0)return;
                    return 0 === r.pipesCount ? (r.flowing = !1, void(C.listenerCount(e, "data") > 0 && b(e))) : void(r.ranOut = !0)
                }

                function v() {
                    this._readableState.ranOut && (this._readableState.ranOut = !1, m(this))
                }

                function b(e, t) {
                    var r = e._readableState;
                    if (r.flowing)throw new Error("Cannot switch to old mode now.");
                    var i = t || !1, o = !1;
                    e.readable = !0, e.pipe = k.prototype.pipe, e.on = e.addListener = k.prototype.on, e.on("readable", function () {
                        o = !0;
                        for (var t; !i && null !== (t = e.read());)e.emit("data", t);
                        null === t && (o = !1, e._readableState.needReadable = !0)
                    }), e.pause = function () {
                        i = !0, this.emit("pause")
                    }, e.resume = function () {
                        i = !1, o ? n.nextTick(function () {
                            e.emit("readable")
                        }) : this.read(0), this.emit("resume")
                    }, e.emit("readable")
                }

                function y(e, t) {
                    var n, r = t.buffer, i = t.length, o = !!t.decoder, s = !!t.objectMode;
                    if (0 === r.length)return null;
                    if (0 === i)n = null; else if (s)n = r.shift(); else if (!e || e >= i)n = o ? r.join("") : L.concat(r, i), r.length = 0; else if (e < r[0].length) {
                        var a = r[0];
                        n = a.slice(0, e), r[0] = a.slice(e)
                    } else if (e === r[0].length)n = r.shift(); else {
                        n = o ? "" : new L(e);
                        for (var u = 0, c = 0, h = r.length; h > c && e > u; c++) {
                            var a = r[0], f = Math.min(e - u, a.length);
                            o ? n += a.slice(0, f) : a.copy(n, u, 0, f), f < a.length ? r[0] = a.slice(f) : r.shift(), u += f
                        }
                    }
                    return n
                }

                function w(e) {
                    var t = e._readableState;
                    if (t.length > 0)throw new Error("endReadable called on non-empty stream");
                    !t.endEmitted && t.calledRead && (t.ended = !0, n.nextTick(function () {
                        t.endEmitted || 0 !== t.length || (t.endEmitted = !0, e.readable = !1, e.emit("end"))
                    }))
                }

                function _(e, t) {
                    for (var n = 0, r = e.length; r > n; n++)t(e[n], n)
                }

                function E(e, t) {
                    for (var n = 0, r = e.length; r > n; n++)if (e[n] === t)return n;
                    return -1
                }

                t.exports = i;
                var S = e("isarray"), L = e("buffer").Buffer;
                i.ReadableState = r;
                var C = e("events").EventEmitter;
                C.listenerCount || (C.listenerCount = function (e, t) {
                    return e.listeners(t).length
                });
                var k = e("stream"), I = e("core-util-is");
                I.inherits = e("inherits");
                var A;
                I.inherits(i, k), i.prototype.push = function (e, t) {
                    var n = this._readableState;
                    return "string" != typeof e || n.objectMode || (t = t || n.defaultEncoding, t !== n.encoding && (e = new L(e, t), t = "")), o(this, n, e, t, !1)
                }, i.prototype.unshift = function (e) {
                    var t = this._readableState;
                    return o(this, t, e, "", !0)
                }, i.prototype.setEncoding = function (t) {
                    A || (A = e("string_decoder/").StringDecoder), this._readableState.decoder = new A(t), this._readableState.encoding = t
                };
                var M = 8388608;
                i.prototype.read = function (e) {
                    var t = this._readableState;
                    t.calledRead = !0;
                    var n = e;
                    if (("number" != typeof e || e > 0) && (t.emittedReadable = !1), 0 === e && t.needReadable && (t.length >= t.highWaterMark || t.ended))return f(this), null;
                    if (e = u(e, t), 0 === e && t.ended)return 0 === t.length && w(this), null;
                    var r = t.needReadable;
                    t.length - e <= t.highWaterMark && (r = !0), (t.ended || t.reading) && (r = !1), r && (t.reading = !0, t.sync = !0, 0 === t.length && (t.needReadable = !0), this._read(t.highWaterMark), t.sync = !1), r && !t.reading && (e = u(n, t));
                    var i;
                    return i = e > 0 ? y(e, t) : null, null === i && (t.needReadable = !0, e = 0), t.length -= e, 0 !== t.length || t.ended || (t.needReadable = !0), t.ended && !t.endEmitted && 0 === t.length && w(this), i
                }, i.prototype._read = function () {
                    this.emit("error", new Error("not implemented"))
                }, i.prototype.pipe = function (e, t) {
                    function r(e) {
                        e === h && o()
                    }

                    function i() {
                        e.end()
                    }

                    function o() {
                        e.removeListener("close", a), e.removeListener("finish", u), e.removeListener("drain", p), e.removeListener("error", s), e.removeListener("unpipe", r), h.removeListener("end", i), h.removeListener("end", o), (!e._writableState || e._writableState.needDrain) && p()
                    }

                    function s(t) {
                        c(), e.removeListener("error", s), 0 === C.listenerCount(e, "error") && e.emit("error", t)
                    }

                    function a() {
                        e.removeListener("finish", u), c()
                    }

                    function u() {
                        e.removeListener("close", a), c()
                    }

                    function c() {
                        h.unpipe(e)
                    }

                    var h = this, f = this._readableState;
                    switch (f.pipesCount) {
                        case 0:
                            f.pipes = e;
                            break;
                        case 1:
                            f.pipes = [f.pipes, e];
                            break;
                        default:
                            f.pipes.push(e)
                    }
                    f.pipesCount += 1;
                    var l = (!t || t.end !== !1) && e !== n.stdout && e !== n.stderr, d = l ? i : o;
                    f.endEmitted ? n.nextTick(d) : h.once("end", d), e.on("unpipe", r);
                    var p = g(h);
                    return e.on("drain", p), e._events && e._events.error ? S(e._events.error) ? e._events.error.unshift(s) : e._events.error = [s, e._events.error] : e.on("error", s), e.once("close", a), e.once("finish", u), e.emit("pipe", h), f.flowing || (this.on("readable", v), f.flowing = !0, n.nextTick(function () {
                        m(h)
                    })), e
                }, i.prototype.unpipe = function (e) {
                    var t = this._readableState;
                    if (0 === t.pipesCount)return this;
                    if (1 === t.pipesCount)return e && e !== t.pipes ? this : (e || (e = t.pipes), t.pipes = null, t.pipesCount = 0, this.removeListener("readable", v), t.flowing = !1, e && e.emit("unpipe", this), this);
                    if (!e) {
                        var n = t.pipes, r = t.pipesCount;
                        t.pipes = null, t.pipesCount = 0, this.removeListener("readable", v), t.flowing = !1;
                        for (var i = 0; r > i; i++)n[i].emit("unpipe", this);
                        return this
                    }
                    var i = E(t.pipes, e);
                    return -1 === i ? this : (t.pipes.splice(i, 1), t.pipesCount -= 1, 1 === t.pipesCount && (t.pipes = t.pipes[0]), e.emit("unpipe", this), this)
                }, i.prototype.on = function (e, t) {
                    var n = k.prototype.on.call(this, e, t);
                    if ("data" !== e || this._readableState.flowing || b(this), "readable" === e && this.readable) {
                        var r = this._readableState;
                        r.readableListening || (r.readableListening = !0, r.emittedReadable = !1, r.needReadable = !0, r.reading ? r.length && f(this, r) : this.read(0))
                    }
                    return n
                }, i.prototype.addListener = i.prototype.on, i.prototype.resume = function () {
                    b(this), this.read(0), this.emit("resume")
                }, i.prototype.pause = function () {
                    b(this, !0), this.emit("pause")
                }, i.prototype.wrap = function (e) {
                    var t = this._readableState, n = !1, r = this;
                    e.on("end", function () {
                        if (t.decoder && !t.ended) {
                            var e = t.decoder.end();
                            e && e.length && r.push(e)
                        }
                        r.push(null)
                    }), e.on("data", function (i) {
                        if (t.decoder && (i = t.decoder.write(i)), i && (t.objectMode || i.length)) {
                            var o = r.push(i);
                            o || (n = !0, e.pause())
                        }
                    });
                    for (var i in e)"function" == typeof e[i] && "undefined" == typeof this[i] && (this[i] = function (t) {
                        return function () {
                            return e[t].apply(e, arguments)
                        }
                    }(i));
                    var o = ["error", "close", "destroy", "pause", "resume"];
                    return _(o, function (t) {
                        e.on(t, r.emit.bind(r, t))
                    }), r._read = function () {
                        n && (n = !1, e.resume())
                    }, r
                }, i._fromList = y
            }).call(this, e("_process"))
        }, {
            _process: 6,
            buffer: 1,
            "core-util-is": 13,
            events: 4,
            inherits: 25,
            isarray: 5,
            stream: 19,
            "string_decoder/": 14
        }],
        11: [function (e, t) {
            function n(e, t) {
                this.afterTransform = function (e, n) {
                    return r(t, e, n)
                }, this.needTransform = !1, this.transforming = !1, this.writecb = null, this.writechunk = null
            }

            function r(e, t, n) {
                var r = e._transformState;
                r.transforming = !1;
                var i = r.writecb;
                if (!i)return e.emit("error", new Error("no writecb in Transform class"));
                r.writechunk = null, r.writecb = null, null !== n && void 0 !== n && e.push(n), i && i(t);
                var o = e._readableState;
                o.reading = !1, (o.needReadable || o.length < o.highWaterMark) && e._read(o.highWaterMark)
            }

            function i(e) {
                if (!(this instanceof i))return new i(e);
                s.call(this, e);
                var t = (this._transformState = new n(e, this), this);
                this._readableState.needReadable = !0, this._readableState.sync = !1, this.once("finish", function () {
                    "function" == typeof this._flush ? this._flush(function (e) {
                        o(t, e)
                    }) : o(t)
                })
            }

            function o(e, t) {
                if (t)return e.emit("error", t);
                var n = e._writableState, r = (e._readableState, e._transformState);
                if (n.length)throw new Error("calling transform done when ws.length != 0");
                if (r.transforming)throw new Error("calling transform done when still transforming");
                return e.push(null)
            }

            t.exports = i;
            var s = e("./_stream_duplex"), a = e("core-util-is");
            a.inherits = e("inherits"), a.inherits(i, s), i.prototype.push = function (e, t) {
                return this._transformState.needTransform = !1, s.prototype.push.call(this, e, t)
            }, i.prototype._transform = function () {
                throw new Error("not implemented")
            }, i.prototype._write = function (e, t, n) {
                var r = this._transformState;
                if (r.writecb = n, r.writechunk = e, r.writeencoding = t, !r.transforming) {
                    var i = this._readableState;
                    (r.needTransform || i.needReadable || i.length < i.highWaterMark) && this._read(i.highWaterMark)
                }
            }, i.prototype._read = function () {
                var e = this._transformState;
                null !== e.writechunk && e.writecb && !e.transforming ? (e.transforming = !0, this._transform(e.writechunk, e.writeencoding, e.afterTransform)) : e.needTransform = !0
            }
        }, {"./_stream_duplex": 8, "core-util-is": 13, inherits: 25}],
        12: [function (e, t) {
            (function (n) {
                function r(e, t, n) {
                    this.chunk = e, this.encoding = t, this.callback = n
                }

                function i(e, t) {
                    e = e || {};
                    var n = e.highWaterMark;
                    this.highWaterMark = n || 0 === n ? n : 16384, this.objectMode = !!e.objectMode, this.highWaterMark = ~~this.highWaterMark, this.needDrain = !1, this.ending = !1, this.ended = !1, this.finished = !1;
                    var r = e.decodeStrings === !1;
                    this.decodeStrings = !r, this.defaultEncoding = e.defaultEncoding || "utf8", this.length = 0, this.writing = !1, this.sync = !0, this.bufferProcessing = !1, this.onwrite = function (e) {
                        d(t, e)
                    }, this.writecb = null, this.writelen = 0, this.buffer = [], this.errorEmitted = !1
                }

                function o(t) {
                    var n = e("./_stream_duplex");
                    return this instanceof o || this instanceof n ? (this._writableState = new i(t, this), this.writable = !0, void E.call(this)) : new o(t)
                }

                function s(e, t, r) {
                    var i = new Error("write after end");
                    e.emit("error", i), n.nextTick(function () {
                        r(i)
                    })
                }

                function a(e, t, r, i) {
                    var o = !0;
                    if (!w.isBuffer(r) && "string" != typeof r && null !== r && void 0 !== r && !t.objectMode) {
                        var s = new TypeError("Invalid non-string/buffer chunk");
                        e.emit("error", s), n.nextTick(function () {
                            i(s)
                        }), o = !1
                    }
                    return o
                }

                function u(e, t, n) {
                    return e.objectMode || e.decodeStrings === !1 || "string" != typeof t || (t = new w(t, n)), t
                }

                function c(e, t, n, i, o) {
                    n = u(t, n, i), w.isBuffer(n) && (i = "buffer");
                    var s = t.objectMode ? 1 : n.length;
                    t.length += s;
                    var a = t.length < t.highWaterMark;
                    return a || (t.needDrain = !0), t.writing ? t.buffer.push(new r(n, i, o)) : h(e, t, s, n, i, o), a
                }

                function h(e, t, n, r, i, o) {
                    t.writelen = n, t.writecb = o, t.writing = !0, t.sync = !0, e._write(r, i, t.onwrite), t.sync = !1
                }

                function f(e, t, r, i, o) {
                    r ? n.nextTick(function () {
                        o(i)
                    }) : o(i), e._writableState.errorEmitted = !0, e.emit("error", i)
                }

                function l(e) {
                    e.writing = !1, e.writecb = null, e.length -= e.writelen, e.writelen = 0
                }

                function d(e, t) {
                    var r = e._writableState, i = r.sync, o = r.writecb;
                    if (l(r), t)f(e, r, i, t, o); else {
                        var s = v(e, r);
                        s || r.bufferProcessing || !r.buffer.length || m(e, r), i ? n.nextTick(function () {
                            p(e, r, s, o)
                        }) : p(e, r, s, o)
                    }
                }

                function p(e, t, n, r) {
                    n || g(e, t), r(), n && b(e, t)
                }

                function g(e, t) {
                    0 === t.length && t.needDrain && (t.needDrain = !1, e.emit("drain"))
                }

                function m(e, t) {
                    t.bufferProcessing = !0;
                    for (var n = 0; n < t.buffer.length; n++) {
                        var r = t.buffer[n], i = r.chunk, o = r.encoding, s = r.callback, a = t.objectMode ? 1 : i.length;
                        if (h(e, t, a, i, o, s), t.writing) {
                            n++;
                            break
                        }
                    }
                    t.bufferProcessing = !1, n < t.buffer.length ? t.buffer = t.buffer.slice(n) : t.buffer.length = 0
                }

                function v(e, t) {
                    return t.ending && 0 === t.length && !t.finished && !t.writing
                }

                function b(e, t) {
                    var n = v(e, t);
                    return n && (t.finished = !0, e.emit("finish")), n
                }

                function y(e, t, r) {
                    t.ending = !0, b(e, t), r && (t.finished ? n.nextTick(r) : e.once("finish", r)), t.ended = !0
                }

                t.exports = o;
                var w = e("buffer").Buffer;
                o.WritableState = i;
                var _ = e("core-util-is");
                _.inherits = e("inherits");
                var E = e("stream");
                _.inherits(o, E), o.prototype.pipe = function () {
                    this.emit("error", new Error("Cannot pipe. Not readable."))
                }, o.prototype.write = function (e, t, n) {
                    var r = this._writableState, i = !1;
                    return "function" == typeof t && (n = t, t = null), w.isBuffer(e) ? t = "buffer" : t || (t = r.defaultEncoding), "function" != typeof n && (n = function () {
                    }), r.ended ? s(this, r, n) : a(this, r, e, n) && (i = c(this, r, e, t, n)), i
                }, o.prototype._write = function (e, t, n) {
                    n(new Error("not implemented"))
                }, o.prototype.end = function (e, t, n) {
                    var r = this._writableState;
                    "function" == typeof e ? (n = e, e = null, t = null) : "function" == typeof t && (n = t, t = null), "undefined" != typeof e && null !== e && this.write(e, t), r.ending || r.finished || y(this, r, n)
                }
            }).call(this, e("_process"))
        }, {"./_stream_duplex": 8, _process: 6, buffer: 1, "core-util-is": 13, inherits: 25, stream: 19}],
        13: [function (e, t, n) {
            (function (e) {
                function t(e) {
                    return Array.isArray(e)
                }

                function r(e) {
                    return "boolean" == typeof e
                }

                function i(e) {
                    return null === e
                }

                function o(e) {
                    return null == e
                }

                function s(e) {
                    return "number" == typeof e
                }

                function a(e) {
                    return "string" == typeof e
                }

                function u(e) {
                    return "symbol" == typeof e
                }

                function c(e) {
                    return void 0 === e
                }

                function h(e) {
                    return f(e) && "[object RegExp]" === v(e)
                }

                function f(e) {
                    return "object" == typeof e && null !== e
                }

                function l(e) {
                    return f(e) && "[object Date]" === v(e)
                }

                function d(e) {
                    return f(e) && ("[object Error]" === v(e) || e instanceof Error)
                }

                function p(e) {
                    return "function" == typeof e
                }

                function g(e) {
                    return null === e || "boolean" == typeof e || "number" == typeof e || "string" == typeof e || "symbol" == typeof e || "undefined" == typeof e
                }

                function m(t) {
                    return e.isBuffer(t)
                }

                function v(e) {
                    return Object.prototype.toString.call(e)
                }

                n.isArray = t, n.isBoolean = r, n.isNull = i, n.isNullOrUndefined = o, n.isNumber = s, n.isString = a, n.isSymbol = u, n.isUndefined = c, n.isRegExp = h, n.isObject = f, n.isDate = l, n.isError = d, n.isFunction = p, n.isPrimitive = g, n.isBuffer = m
            }).call(this, e("buffer").Buffer)
        }, {buffer: 1}],
        14: [function (e, t, n) {
            function r(e) {
                if (e && !u(e))throw new Error("Unknown encoding: " + e)
            }

            function i(e) {
                return e.toString(this.encoding)
            }

            function o(e) {
                var t = this.charReceived = e.length % 2;
                return this.charLength = t ? 2 : 0, t
            }

            function s(e) {
                var t = this.charReceived = e.length % 3;
                return this.charLength = t ? 3 : 0, t
            }

            var a = e("buffer").Buffer, u = a.isEncoding || function (e) {
                    switch (e && e.toLowerCase()) {
                        case"hex":
                        case"utf8":
                        case"utf-8":
                        case"ascii":
                        case"binary":
                        case"base64":
                        case"ucs2":
                        case"ucs-2":
                        case"utf16le":
                        case"utf-16le":
                        case"raw":
                            return !0;
                        default:
                            return !1
                    }
                }, c = n.StringDecoder = function (e) {
                switch (this.encoding = (e || "utf8").toLowerCase().replace(/[-_]/, ""), r(e), this.encoding) {
                    case"utf8":
                        this.surrogateSize = 3;
                        break;
                    case"ucs2":
                    case"utf16le":
                        this.surrogateSize = 2, this.detectIncompleteChar = o;
                        break;
                    case"base64":
                        this.surrogateSize = 3, this.detectIncompleteChar = s;
                        break;
                    default:
                        return void(this.write = i)
                }
                this.charBuffer = new a(6), this.charReceived = 0, this.charLength = 0
            };
            c.prototype.write = function (e) {
                for (var t = "", n = 0; this.charLength;) {
                    var r = e.length >= this.charLength - this.charReceived ? this.charLength - this.charReceived : e.length;
                    if (e.copy(this.charBuffer, this.charReceived, n, r), this.charReceived += r - n, n = r, this.charReceived < this.charLength)return "";
                    t = this.charBuffer.slice(0, this.charLength).toString(this.encoding);
                    var i = t.charCodeAt(t.length - 1);
                    if (!(i >= 55296 && 56319 >= i)) {
                        if (this.charReceived = this.charLength = 0, r == e.length)return t;
                        e = e.slice(r, e.length);
                        break
                    }
                    this.charLength += this.surrogateSize, t = ""
                }
                var o = this.detectIncompleteChar(e), s = e.length;
                this.charLength && (e.copy(this.charBuffer, 0, e.length - o, s), this.charReceived = o, s -= o), t += e.toString(this.encoding, 0, s);
                var s = t.length - 1, i = t.charCodeAt(s);
                if (i >= 55296 && 56319 >= i) {
                    var a = this.surrogateSize;
                    return this.charLength += a, this.charReceived += a, this.charBuffer.copy(this.charBuffer, a, 0, a), this.charBuffer.write(t.charAt(t.length - 1), this.encoding), t.substring(0, s)
                }
                return t
            }, c.prototype.detectIncompleteChar = function (e) {
                for (var t = e.length >= 3 ? 3 : e.length; t > 0; t--) {
                    var n = e[e.length - t];
                    if (1 == t && n >> 5 == 6) {
                        this.charLength = 2;
                        break
                    }
                    if (2 >= t && n >> 4 == 14) {
                        this.charLength = 3;
                        break
                    }
                    if (3 >= t && n >> 3 == 30) {
                        this.charLength = 4;
                        break
                    }
                }
                return t
            }, c.prototype.end = function (e) {
                var t = "";
                if (e && e.length && (t = this.write(e)), this.charReceived) {
                    var n = this.charReceived, r = this.charBuffer, i = this.encoding;
                    t += r.slice(0, n).toString(i)
                }
                return t
            }
        }, {buffer: 1}],
        15: [function (e, t) {
            t.exports = e("./lib/_stream_passthrough.js")
        }, {"./lib/_stream_passthrough.js": 9}],
        16: [function (e, t, n) {
            n = t.exports = e("./lib/_stream_readable.js"), n.Readable = n, n.Writable = e("./lib/_stream_writable.js"), n.Duplex = e("./lib/_stream_duplex.js"), n.Transform = e("./lib/_stream_transform.js"), n.PassThrough = e("./lib/_stream_passthrough.js")
        }, {
            "./lib/_stream_duplex.js": 8,
            "./lib/_stream_passthrough.js": 9,
            "./lib/_stream_readable.js": 10,
            "./lib/_stream_transform.js": 11,
            "./lib/_stream_writable.js": 12
        }],
        17: [function (e, t) {
            t.exports = e("./lib/_stream_transform.js")
        }, {"./lib/_stream_transform.js": 11}],
        18: [function (e, t) {
            t.exports = e("./lib/_stream_writable.js")
        }, {"./lib/_stream_writable.js": 12}],
        19: [function (e, t) {
            function n() {
                r.call(this)
            }

            t.exports = n;
            var r = e("events").EventEmitter, i = e("inherits");
            i(n, r), n.Readable = e("readable-stream/readable.js"), n.Writable = e("readable-stream/writable.js"), n.Duplex = e("readable-stream/duplex.js"), n.Transform = e("readable-stream/transform.js"), n.PassThrough = e("readable-stream/passthrough.js"), n.Stream = n, n.prototype.pipe = function (e, t) {
                function n(t) {
                    e.writable && !1 === e.write(t) && c.pause && c.pause()
                }

                function i() {
                    c.readable && c.resume && c.resume()
                }

                function o() {
                    h || (h = !0, e.end())
                }

                function s() {
                    h || (h = !0, "function" == typeof e.destroy && e.destroy())
                }

                function a(e) {
                    if (u(), 0 === r.listenerCount(this, "error"))throw e
                }

                function u() {
                    c.removeListener("data", n), e.removeListener("drain", i), c.removeListener("end", o), c.removeListener("close", s), c.removeListener("error", a), e.removeListener("error", a), c.removeListener("end", u), c.removeListener("close", u), e.removeListener("close", u)
                }

                var c = this;
                c.on("data", n), e.on("drain", i), e._isStdio || t && t.end === !1 || (c.on("end", o), c.on("close", s));
                var h = !1;
                return c.on("error", a), e.on("error", a), c.on("end", u), c.on("close", u), e.on("close", u), e.emit("pipe", c), e
            }
        }, {
            events: 4,
            inherits: 25,
            "readable-stream/duplex.js": 7,
            "readable-stream/passthrough.js": 15,
            "readable-stream/readable.js": 16,
            "readable-stream/transform.js": 17,
            "readable-stream/writable.js": 18
        }],
        20: [function (e, t, n) {
            function r() {
                return "WebkitAppearance" in document.documentElement.style || window.console && (console.firebug || console.exception && console.table) || navigator.userAgent.toLowerCase().match(/firefox\/(\d+)/) && parseInt(RegExp.$1, 10) >= 31
            }

            function i() {
                var e = arguments, t = this.useColors;
                if (e[0] = (t ? "%c" : "") + this.namespace + (t ? " %c" : " ") + e[0] + (t ? "%c " : " ") + "+" + n.humanize(this.diff), !t)return e;
                var r = "color: " + this.color;
                e = [e[0], r, "color: inherit"].concat(Array.prototype.slice.call(e, 1));
                var i = 0, o = 0;
                return e[0].replace(/%[a-z%]/g, function (e) {
                    "%%" !== e && (i++, "%c" === e && (o = i))
                }), e.splice(o, 0, r), e
            }

            function o() {
                return "object" == typeof console && "function" == typeof console.log && Function.prototype.apply.call(console.log, console, arguments)
            }

            function s(e) {
                try {
                    null == e ? localStorage.removeItem("debug") : localStorage.debug = e
                } catch (t) {
                }
            }

            function a() {
                var e;
                try {
                    e = localStorage.debug
                } catch (t) {
                }
                return e
            }

            n = t.exports = e("./debug"), n.log = o, n.formatArgs = i, n.save = s, n.load = a, n.useColors = r, n.colors = ["lightseagreen", "forestgreen", "goldenrod", "dodgerblue", "darkorchid", "crimson"], n.formatters.j = function (e) {
                return JSON.stringify(e)
            }, n.enable(a())
        }, {"./debug": 21}],
        21: [function (e, t, n) {
            function r() {
                return n.colors[h++ % n.colors.length]
            }

            function i(e) {
                function t() {
                }

                function i() {
                    var e = i, t = +new Date, o = t - (c || t);
                    e.diff = o, e.prev = c, e.curr = t, c = t, null == e.useColors && (e.useColors = n.useColors()), null == e.color && e.useColors && (e.color = r());
                    var s = Array.prototype.slice.call(arguments);
                    s[0] = n.coerce(s[0]), "string" != typeof s[0] && (s = ["%o"].concat(s));
                    var a = 0;
                    s[0] = s[0].replace(/%([a-z%])/g, function (t, r) {
                        if ("%%" === t)return t;
                        a++;
                        var i = n.formatters[r];
                        if ("function" == typeof i) {
                            var o = s[a];
                            t = i.call(e, o), s.splice(a, 1), a--
                        }
                        return t
                    }), "function" == typeof n.formatArgs && (s = n.formatArgs.apply(e, s));
                    var u = i.log || n.log || console.log.bind(console);
                    u.apply(e, s)
                }

                t.enabled = !1, i.enabled = !0;
                var o = n.enabled(e) ? i : t;
                return o.namespace = e, o
            }

            function o(e) {
                n.save(e);
                for (var t = (e || "").split(/[\s,]+/), r = t.length, i = 0; r > i; i++)t[i] && (e = t[i].replace(/\*/g, ".*?"), "-" === e[0] ? n.skips.push(new RegExp("^" + e.substr(1) + "$")) : n.names.push(new RegExp("^" + e + "$")))
            }

            function s() {
                n.enable("")
            }

            function a(e) {
                var t, r;
                for (t = 0, r = n.skips.length; r > t; t++)if (n.skips[t].test(e))return !1;
                for (t = 0, r = n.names.length; r > t; t++)if (n.names[t].test(e))return !0;
                return !1
            }

            function u(e) {
                return e instanceof Error ? e.stack || e.message : e
            }

            n = t.exports = i, n.coerce = u, n.disable = s, n.enable = o, n.enabled = a, n.humanize = e("ms"), n.names = [], n.skips = [], n.formatters = {};
            var c, h = 0
        }, {ms: 22}],
        22: [function (e, t) {
            function n(e) {
                var t = /^((?:\d+)?\.?\d+) *(ms|seconds?|s|minutes?|m|hours?|h|days?|d|years?|y)?$/i.exec(e);
                if (t) {
                    var n = parseFloat(t[1]), r = (t[2] || "ms").toLowerCase();
                    switch (r) {
                        case"years":
                        case"year":
                        case"y":
                            return n * h;
                        case"days":
                        case"day":
                        case"d":
                            return n * c;
                        case"hours":
                        case"hour":
                        case"h":
                            return n * u;
                        case"minutes":
                        case"minute":
                        case"m":
                            return n * a;
                        case"seconds":
                        case"second":
                        case"s":
                            return n * s;
                        case"ms":
                            return n
                    }
                }
            }

            function r(e) {
                return e >= c ? Math.round(e / c) + "d" : e >= u ? Math.round(e / u) + "h" : e >= a ? Math.round(e / a) + "m" : e >= s ? Math.round(e / s) + "s" : e + "ms"
            }

            function i(e) {
                return o(e, c, "day") || o(e, u, "hour") || o(e, a, "minute") || o(e, s, "second") || e + " ms"
            }

            function o(e, t, n) {
                return t > e ? void 0 : 1.5 * t > e ? Math.floor(e / t) + " " + n : Math.ceil(e / t) + " " + n + "s"
            }

            var s = 1e3, a = 60 * s, u = 60 * a, c = 24 * u, h = 365.25 * c;
            t.exports = function (e, t) {
                return t = t || {}, "string" == typeof e ? n(e) : t.long ? i(e) : r(e)
            }
        }, {}],
        23: [function (e, t) {
            t.exports = function (e) {
                for (var t, n = [].slice.call(arguments, 1), r = 0, i = n.length; i > r; r++) {
                    t = n[r];
                    for (var o in t)e[o] = t[o]
                }
                return e
            }
        }, {}],
        24: [function (e, t) {
            var n = t.exports = function (e, t) {
                if (t || (t = 16), void 0 === e && (e = 128), 0 >= e)return "0";
                for (var r = Math.log(Math.pow(2, e)) / Math.log(t), i = 2; 1 / 0 === r; i *= 2)r = Math.log(Math.pow(2, e / i)) / Math.log(t) * i;
                for (var o = r - Math.floor(r), s = "", i = 0; i < Math.floor(r); i++) {
                    var a = Math.floor(Math.random() * t).toString(t);
                    s = a + s
                }
                if (o) {
                    var u = Math.pow(t, o), a = Math.floor(Math.random() * u).toString(t);
                    s = a + s
                }
                var c = parseInt(s, t);
                return 1 / 0 !== c && c >= Math.pow(2, e) ? n(e, t) : s
            };
            n.rack = function (e, t, r) {
                var i = function (i) {
                    var s = 0;
                    do {
                        if (s++ > 10) {
                            if (!r)throw new Error("too many ID collisions, use more bits");
                            e += r
                        }
                        var a = n(e, t)
                    } while (Object.hasOwnProperty.call(o, a));
                    return o[a] = i, a
                }, o = i.hats = {};
                return i.get = function (e) {
                    return i.hats[e]
                }, i.set = function (e, t) {
                    return i.hats[e] = t, i
                }, i.bits = e || 128, i.base = t || 16, i
            }
        }, {}],
        25: [function (e, t) {
            t.exports = "function" == typeof Object.create ? function (e, t) {
                e.super_ = t, e.prototype = Object.create(t.prototype, {
                    constructor: {
                        value: e,
                        enumerable: !1,
                        writable: !0,
                        configurable: !0
                    }
                })
            } : function (e, t) {
                e.super_ = t;
                var n = function () {
                };
                n.prototype = t.prototype, e.prototype = new n, e.prototype.constructor = e
            }
        }, {}],
        26: [function (e, t) {
            function n(e) {
                return r(e) || i(e)
            }

            function r(e) {
                return e instanceof Int8Array || e instanceof Int16Array || e instanceof Int32Array || e instanceof Uint8Array || e instanceof Uint16Array || e instanceof Uint32Array || e instanceof Float32Array || e instanceof Float64Array
            }

            function i(e) {
                return s[o.call(e)]
            }

            t.exports = n, n.strict = r, n.loose = i;
            var o = Object.prototype.toString, s = {
                "[object Int8Array]": !0,
                "[object Int16Array]": !0,
                "[object Int32Array]": !0,
                "[object Uint8Array]": !0,
                "[object Uint16Array]": !0,
                "[object Uint32Array]": !0,
                "[object Float32Array]": !0,
                "[object Float64Array]": !0
            }
        }, {}],
        27: [function (e, t) {
            function n(e) {
                var t = function () {
                    return t.called ? t.value : (t.called = !0, t.value = e.apply(this, arguments))
                };
                return t.called = !1, t
            }

            t.exports = n, n.proto = n(function () {
                Object.defineProperty(Function.prototype, "once", {
                    value: function () {
                        return n(this)
                    }, configurable: !0
                })
            })
        }, {}],
        28: [function (e, t) {
            (function (e) {
                t.exports = function (t) {
                    return "function" == typeof e._augment && e._useTypedArrays ? e._augment(t) : new e(t)
                }
            }).call(this, e("buffer").Buffer)
        }, {buffer: 1}]
    }, {}, [])("./")
});
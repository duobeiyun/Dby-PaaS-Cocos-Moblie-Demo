cc.Class({
    extends: cc.Component,
    properties: {
        dbyClient: {
            default: null,
            type: Object
        },
        dbyInst: {
            default: null,
            type: Object
        },
        sprites: {
            default: null,
            type: Object
        },
        uids: {
            default: null,
            type: Object
        },
        dbyTag: "[dby] js",
        headerW: 280,
        headerH: 210,
        headerOffset: 20,
    },
    onLoad: function () {
        var appKey = "47f90cb3bb2345ed9d010be3c299eca4";
        var appId = "2f73114f06f4483da779cb1968424625";
        var sprites = {};
        this.sprites = sprites;
        const uids = new Set();
        this.uids = uids;
        this.uids.add(0);
        this.dbyInst = new adbyCreator();
        this.dbyInst.initialize(appKey,appId);
        // this.dbyInst.enableVideo();
        // this.dbyInst.enableVideoObserver();
        this.dbyInst.joinChannel("5375", "5375", "5375");

        this.dbyInst.onLeaveChannel = function (rtcStats) {
            console.log("[dby] js  onLeaveChannel");
        };

        this.dbyInst.onJoinChannelSuccess = function (channelName, uid, elapsed) {
            console.log("[dby] js  onJoinChannelSuccess");
        };

        this.dbyInst.onUserJoined = function (uid, elapsed) {
            uids.add(uid);
            console.log("[dby] js onUserJoined uid = %d", uid);
        };

        this.dbyInst.onUserOffline = function (uid, reason) {
            uids.delete(uid);
            sprites[uid] = null;
            console.log("[dby] js onUserOffline uid = %d", uid);
        };

        setInterval(this.getTexture.bind(this), 40);
    },

    getTexture: function () {
        console.log("[dby] js getTexture");
        var e = !0, t = !1, o = void 0;
        try {
            for (var i, a = this.uids[Symbol.iterator](); !(e = (i = a.next()).done); e = !0) {
                var l = i.value, n = this.dbyInst.updateTexture(l);
                this.updateTexture(l, n);
            }
        } catch (e) {
            t = !0;
            o = e;
        } finally {
            try {
                !e && a.return && a.return();
            } finally {
                if (t) throw o;
            }
        }
    },

    updateTexture: function (uid, texture) {
        var r = this.sprites[uid];
        if (null == r) {
            var n = new cc.SpriteFrame();
            n.setTexture(texture);
            var a = new cc.Node("Sprite");
            (r = a.addComponent(cc.Sprite)).spriteFrame = n;
            a.x = 0;
            a.y = 0;
            a.setContentSize(this.headerW, this.headerH);
            a.parent = this.node;
            this.sprites[uid] = r;
            this.updateHeadersDisplay();
        } else {
            r.spriteFrame.setTexture(texture);
            r.node.setContentSize(this.headerW, this.headerH);
        }
    },

    updateHeadersDisplay: function () {
        var e = cc.director.getWinSize(), t = -e.width / 2, r = -e.height / 2, n = 0;
        for (var a in this.sprites) {
            if (this.sprites[a] != null)
            {
                var i = this.sprites[a].node;
                if (a == 0) {
                    i.anchorX = 0;
                    i.anchorY = 0;
                    i.x = e.width / 2 - this.headerW;
                    i.y = e.height / 2 - this.headerH;
                } else {
                    i.anchorX = 0;
                    i.anchorY = 0;
                    i.x = n * this.headerW + n * this.headerOffset + t;
                    i.y = r;
                    n++;
                }
            }
        }
    }
});
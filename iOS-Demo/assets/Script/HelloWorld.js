cc.Class({
    extends: cc.Component,

    properties: {
        label: {
            default: null,
            type: cc.Label
        },

        dbyClient:{
            default: null,
            type: Object
        },
        dbyInst: {
            default: null,
            type: Object
        },

        uids:{
            default: null,
            type: Object
        },
        sprites: {
            default: null,
            type: Object
        },
        headerW: 280,
        headerH: 210,
        headerOffset: 20,
        // defaults, set visually when attaching this script to the Canvas
        text: 'Hello, World!'
    },

    // use this for initialization
    onLoad: function () {
        this.label.string = this.text;
        var appId = "your appId";
        var appKey = "youra appKey";

        this.sprites = {};

        this.dbyInst = new dbyCreator();
        this.dbyInst.initialize(appId,appKey);

        var channelId = "654321";
        var uid = "9528";
        var nickname = "nickname";
        this.dbyInst.joinChannel(channelId, uid, nickname);

        const uids = new Set();
        this.uids = uids;
        this.uids.add(uid);

        this.dbyInst.enableVideoObserver();
        this.dbyInst.enableVideo();
        this.dbyInst.enableAudio();
        this.dbyInst.onJoinChannelSuccess = function(channelId, uid, nickname) {
            console.log("onJoinChannelSuccess");
        };

        this.dbyInst.onUserJoined = function(uid) {
            console.log("onUserJoined uid = %s", uid);
            uids.add(uid);
        };

        this.dbyInst.onUserOffline = function(uid) {
            console.log("onUserOffline uid = %s", uid);
            uids.delete(uid);
        };

        this.dbyInst.onLeaveChannel = function() {
            console.log("onLeaveChannel");
        };

        setInterval(this.getTexture.bind(this), 40);
    },

    // called every frame
    update: function (dt) {

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
        console.log("[dby] js updateTexture, uid = %s, before",uid);
        var r = this.sprites[uid];
        console.log("[dby] js updateTexture, uid = %s, after",uid);
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
            console.log("[dby] js updateTexture, not null");
            r.spriteFrame.setTexture(texture);
            r.node.setContentSize(this.headerW, this.headerH);
        }
    },

    updateHeadersDisplay: function () {
        console.log("[dby] js updateHeadersDisplay");
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

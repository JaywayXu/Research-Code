// pages/introduce/introduce.js
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.submit()
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },

  submit: function() {
    var that = this;
    wx.request({
      url: 'https://www.baidu.com',
      // data: {
      //   acc_nbr: JSON.stringify("ls"),
      //   grade1: JSON.stringify(0),  //将数据格式转为JSON
      //   grade2: JSON.stringify(0),  //将数据格式转为JSON
      //   grade3: JSON.stringify(0),  //将数据格式转为JSON
      //   txt1: JSON.stringify("txt1"),
      //   txt2: JSON.stringify("txt2"),
      //   txt3: JSON.stringify("txt3")
      // },
      method: "GET",
      header: {
        'content-type': 'application/json',
        'chartset': 'utf-8'
      }
    })
  },
  success: function (res) {
    console.log(res.data);
    wx.showToast({
      title: res.data,//这里打印出登录成功
      icon: 'success',
      duration: 1000
    });
    var acc_nbr = that.data.phoneNum;
    wx.redirectTo({
      url: '../graderesult/graderesult?phoneNum=' + acc_nbr
    })
  }
})
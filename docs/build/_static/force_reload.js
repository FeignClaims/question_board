(function () {
  if (window.localStorage) {
    if (!localStorage.getItem("firstLoad")) {
      localStorage["firstLoad"] = true;
      window.location.reload();
    } else localStorage.removeItem("firstLoad");
  }
})();
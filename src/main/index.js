var graphConfig = new GitGraph.Template({
    branch: {
        color: "#000000",
        lineWidth: 4,
        spacingX: 60,
        mergeStyle: "straight",
        showLabel: false,                // display branch names on graph
        labelFont: "normal 10pt Arial"
    },
    commit: {
        spacingY: -63,
        dot: {
            size: 15,
            strokeColor: "#000000",
            strokeWidth: 4
        },
        tag: {
            font: "normal 10pt Arial",
            color: "yellow"
        },
        message: {
            color: "black",
            font: "normal 12pt Arial",
            displayAuthor: false,
            displayBranch: false,
            displayHash: false,
        }
    },
    arrow: {
        size: 15,
        offset: 3
    }
});

var config = {
  template: graphConfig,
  mode: "extended",
  orientation: "vertical-reverse"
};


// You can manually fix columns to control the display.
var angPolFixesCol = 0;
var ghPagesCol = 1;
var masterCol = 2;

var gitgraph = new GitGraph(config);

var master = gitgraph.branch({name:"master", column:masterCol});
master.commit({messageDisplay:false});
var ghpages = gitgraph.branch({name:"gh-pages", column:ghPagesCol});
ghpages.commit({messageDisplay:false}).commit({messageDisplay:false}).commit({messageDisplay:false}).commit({messageDisplay:false});
ghpages.merge(master);
var angPol = gitgraph.branch({parentBranch:master, name:"angular-polymer-fixes", column:angPolFixesCol});
angPol.commit({messageDisplay:false}).commit({messageDisplay:false}).commit({messageDisplay:false});
angPol.merge(master);
master.commit({messageDisplay:false}).commit({messageDisplay:false}).commit({messageDisplay:false}).commit({messageDisplay:false});


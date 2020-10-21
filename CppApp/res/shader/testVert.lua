layout = {"aPos", "aColor", "aUV"}
attribute = {
    aPos = {0, 0, 0, 1},
    aColor = {1, 1, 1, 1},
    aUV = {0, 0},
}
verying = {
    oColor = nil,
}
uniform = {
}

function mainxxx()
    hjb()
    print("aPos", aPos[1], aPos[2], aPos[3], aPos[4])
    cr_Position = aPos;
end

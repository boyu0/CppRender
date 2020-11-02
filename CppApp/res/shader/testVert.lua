attribute = {"aPos", "aNormal", "aUV"}
verying = {"uv", "normal", "pos"}
uniform = {}

function main()
    aPos[4] = 1.0

    pos = cr.mul(model, aPos)
    pos[1] = pos[1] / pos[4]
    pos[2] = pos[2] / pos[4]
    pos[3] = pos[3] / pos[4]
    pos[4] = nil

    uv = aUV;
    normal = cr.mul(cr.transpose(cr.inverse(model)), aNormal)

    cr_Position = aPos;
    cr_Position = cr.mul(projection, cr.mul(view, cr.mul(model, cr_Position)))

end



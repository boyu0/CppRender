attribute = {"aPos", "aNormal", "aUV"}
verying = {"uv", "normal", "pos"}
uniform = {}

function main()
    aPos[4] = 1.0
    cr_Position = aPos;
    cr_Position = cr.mul(projection, cr.mul(view, cr.mul(model, cr_Position)))
    uv = aUV;
    normal = aNormal;
    pos = cr.mul(model, aPos)
end


